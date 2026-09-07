#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../../assignment_01/include/csr.h"
#include "../../assignment_01/include/edge.h"
#include "../../assignment_01/include/graph.h"
#include "../../assignment_01/include/timer.h"
#include "../include/a4_graph_reader.h"
#include "../include/pagerank.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0]
             << " <input_graph_file>\n";
        return 1;
    }

    const string filename = argv[1];

    Graph graph;

    double damping;
    double tolerance;
    int maxIterations;

    string errorMessage;

    if (!readPageRankGraph(
            filename,
            graph,
            damping,
            tolerance,
            maxIterations,
            errorMessage))
    {
        cerr << "Error: " << errorMessage << '\n';
        return 1;
    }

    vector<Edge> edgeList = createEdgeList(graph);
    CSR csr = createCSR(edgeList, graph.vertices);

    Timer timer;

    timer.start();

    PageRankResult result =
        pageRank(
            graph.vertices,
            csr,
            damping,
            tolerance,
            maxIterations);

    timer.stop();

    cout << "\n=========================================\n";
    cout << "PageRank\n";
    cout << "=========================================\n";

    cout << "Input File: " << filename << '\n';
    cout << "Number of vertices: " << graph.vertices << '\n';
    cout << "Number of edges: " << graph.edges << '\n';

    cout << "Damping Factor: " << damping << '\n';
    cout << "Tolerance: " << tolerance << '\n';
    cout << "Maximum Iterations: " << maxIterations << '\n';

    if (graph.vertices <= 100)
    {
        cout << "\nVertex PageRanks:\n";

        cout << fixed << setprecision(10);

        for (int vertex = 0; vertex < graph.vertices; vertex++)
        {
            cout << "Vertex " << vertex
                 << " -> Rank " << result.ranks[vertex]
                 << '\n';
        }
    }
    else
    {
        cout << "\nIndividual PageRank values omitted "
                "for large graph.\n";

        cout << "Number of vertices is greater than 100.\n";
    }

    double rankSum = 0.0;

    for (double rank : result.ranks)
    {
        rankSum += rank;
    }

    cout << fixed << setprecision(10);

    cout << "\nRank Sum: "
         << rankSum << '\n';

    cout << "Iterations: "
         << result.iterations << '\n';

    cout << "Converged: "
         << (result.converged ? "YES" : "NO") << '\n';

    cout << setprecision(6);

    cout << "Execution Time: "
         << timer.getElapsedTime()
         << " ms\n";

    cout << "=========================================\n";

    return result.converged ? 0 : 1;
}