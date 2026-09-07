#include "../include/a4_graph_reader.h"

#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

namespace
{
    bool parseGraphHeader(
        const string &line,
        int &vertices,
        int &edges)
    {
        istringstream stream(line);

        if (!(stream >> vertices >> edges))
            return false;

        string extra;

        if (stream >> extra)
            return false;

        return true;
    }

    bool parseAdjacencyLine(
        const string &line,
        int vertices,
        int &vertex,
        vector<int> &neighbours,
        string &errorMessage,
        bool rejectSelfLoop)
    {
        istringstream stream(line);

        int degree;

        if (!(stream >> vertex >> degree))
        {
            errorMessage = "Invalid adjacency-list line.";
            return false;
        }

        if (vertex < 0 || vertex >= vertices)
        {
            errorMessage = "Vertex id out of range: " +
                           to_string(vertex);
            return false;
        }

        if (degree < 0)
        {
            errorMessage = "Negative degree for vertex " +
                           to_string(vertex);
            return false;
        }

        neighbours.clear();

        for (int i = 0; i < degree; ++i)
        {
            int neighbour;

            if (!(stream >> neighbour))
            {
                errorMessage =
                    "Mismatched degree/neighbour count for vertex " +
                    to_string(vertex);

                return false;
            }

            if (neighbour < 0 || neighbour >= vertices)
            {
                errorMessage =
                    "Neighbour vertex out of range: " +
                    to_string(neighbour);

                return false;
            }

            if (rejectSelfLoop && neighbour == vertex)
            {
                errorMessage =
                    "Self-loop detected at vertex " +
                    to_string(vertex);

                return false;
            }

            neighbours.push_back(neighbour);
        }

        // There must not be additional neighbour values.
        string extra;

        if (stream >> extra)
        {
            errorMessage =
                "Mismatched degree/neighbour count for vertex " +
                to_string(vertex);

            return false;
        }

        return true;
    }

    bool buildGraphFromLines(
        ifstream &input,
        Graph &graph,
        bool directed,
        string &errorMessage)
    {
        string line;

        // Read V E.
        do
        {
            if (!getline(input, line))
            {
                errorMessage = "Missing graph header.";
                return false;
            }
        } while (line.empty());

        int vertices;
        int edges;

        if (!parseGraphHeader(line, vertices, edges))
        {
            errorMessage = "Invalid graph header. Expected: V E";
            return false;
        }

        if (vertices <= 0)
        {
            errorMessage = "Number of vertices must be positive.";
            return false;
        }

        if (edges < 0)
        {
            errorMessage = "Number of edges cannot be negative.";
            return false;
        }

        graph.vertices = vertices;
        graph.edges = edges;
        graph.adjacencyList.clear();
        graph.adjacencyList.resize(vertices);

        vector<bool> vertexSeen(vertices, false);

        for (int i = 0; i < vertices; ++i)
        {
            if (!getline(input, line))
            {
                errorMessage =
                    "Missing adjacency-list line for vertex " +
                    to_string(i);

                return false;
            }

            int vertex;
            vector<int> neighbours;

            if (!parseAdjacencyLine(
                    line,
                    vertices,
                    vertex,
                    neighbours,
                    errorMessage,
                    !directed))
            {
                return false;
            }

            if (vertexSeen[vertex])
            {
                errorMessage =
                    "Duplicate adjacency-list entry for vertex " +
                    to_string(vertex);

                return false;
            }

            vertexSeen[vertex] = true;

            for (int neighbour : neighbours)
            {
                Neighbor entry;
                entry.destination = neighbour;
                entry.weight = 1;

                graph.adjacencyList[vertex].push_back(entry);
            }
        }

        for (int vertex = 0; vertex < vertices; ++vertex)
        {
            if (!vertexSeen[vertex])
            {
                errorMessage =
                    "Missing adjacency-list entry for vertex " +
                    to_string(vertex);

                return false;
            }
        }

        // Verify edge count.
        long long adjacencyEntries = 0;

        for (int vertex = 0; vertex < vertices; ++vertex)
        {
            adjacencyEntries +=
                graph.adjacencyList[vertex].size();
        }

        if (directed)
        {
            if (adjacencyEntries != edges)
            {
                errorMessage =
                    "Edge count mismatch. Header specifies " +
                    to_string(edges) +
                    " directed edges, but adjacency lists contain " +
                    to_string(adjacencyEntries) +
                    " entries.";

                return false;
            }
        }
        else
        {
            if (adjacencyEntries != 2LL * edges)
            {
                errorMessage =
                    "Edge count mismatch. Header specifies " +
                    to_string(edges) +
                    " undirected edges, but adjacency lists contain " +
                    to_string(adjacencyEntries) +
                    " entries.";

                return false;
            }

            // Check that every undirected edge is listed both ways.
            for (int vertex = 0; vertex < vertices; ++vertex)
            {
                for (const Neighbor &neighbor :
                     graph.adjacencyList[vertex])
                {
                    bool reverseFound = false;

                    for (const Neighbor &reverse :
                         graph.adjacencyList[neighbor.destination])
                    {
                        if (reverse.destination == vertex)
                        {
                            reverseFound = true;
                            break;
                        }
                    }

                    if (!reverseFound)
                    {
                        errorMessage =
                            "Undirected edge symmetry violation between " +
                            to_string(vertex) +
                            " and " +
                            to_string(neighbor.destination);

                        return false;
                    }
                }
            }
        }

        return true;
    }
}

bool readColoringGraph(
    const string &filename,
    Graph &graph,
    string &errorMessage)
{
    ifstream input(filename);

    if (!input.is_open())
    {
        errorMessage =
            "Unable to open file: " + filename;

        return false;
    }

    return buildGraphFromLines(
        input,
        graph,
        false,
        errorMessage);
}

bool readPageRankGraph(
    const string &filename,
    Graph &graph,
    double &damping,
    double &tolerance,
    int &maxIterations,
    string &errorMessage)
{
    ifstream input(filename);

    if (!input.is_open())
    {
        errorMessage =
            "Unable to open file: " + filename;

        return false;
    }

    if (!buildGraphFromLines(
            input,
            graph,
            true,
            errorMessage))
    {
        return false;
    }

    string line;

    // DAMPING
    if (!getline(input, line))
    {
        errorMessage = "Missing DAMPING parameter.";
        return false;
    }

    {
        istringstream stream(line);
        string keyword;

        if (!(stream >> keyword >> damping) ||
            keyword != "DAMPING")
        {
            errorMessage =
                "Invalid DAMPING parameter.";

            return false;
        }

        string extra;

        if (stream >> extra)
        {
            errorMessage =
                "Invalid DAMPING parameter.";

            return false;
        }
    }

    // TOLERANCE
    if (!getline(input, line))
    {
        errorMessage = "Missing TOLERANCE parameter.";
        return false;
    }

    {
        istringstream stream(line);
        string keyword;

        if (!(stream >> keyword >> tolerance) ||
            keyword != "TOLERANCE")
        {
            errorMessage =
                "Invalid TOLERANCE parameter.";

            return false;
        }

        string extra;

        if (stream >> extra)
        {
            errorMessage =
                "Invalid TOLERANCE parameter.";

            return false;
        }
    }

    // MAX_ITERATIONS
    if (!getline(input, line))
    {
        errorMessage =
            "Missing MAX_ITERATIONS parameter.";

        return false;
    }

    {
        istringstream stream(line);
        string keyword;

        if (!(stream >> keyword >> maxIterations) ||
            keyword != "MAX_ITERATIONS")
        {
            errorMessage =
                "Invalid MAX_ITERATIONS parameter.";

            return false;
        }

        string extra;

        if (stream >> extra)
        {
            errorMessage =
                "Invalid MAX_ITERATIONS parameter.";

            return false;
        }
    }

    if (damping <= 0.0 || damping >= 1.0)
    {
        errorMessage =
            "DAMPING must be greater than 0 and less than 1.";

        return false;
    }

    if (tolerance <= 0.0)
    {
        errorMessage =
            "TOLERANCE must be positive.";

        return false;
    }

    if (maxIterations <= 0)
    {
        errorMessage =
            "MAX_ITERATIONS must be positive.";

        return false;
    }

    return true;
}