#include "../include/graph.h"

using namespace std;

Graph createGraph(int vertices)
{
    Graph graph;
    graph.vertices = vertices;
    graph.edges = 0;
    graph.adjacencyList.resize(vertices);
    return graph;
}

void readGraph(istream &input, Graph &graph)
{
    input >> graph.vertices >> graph.edges;
    graph.adjacencyList.clear();
    graph.adjacencyList.resize(graph.vertices);
    for (int i = 0; i < graph.vertices; i++)
    {
        int vertex;
        int numberOfNeighbors;
        input >> vertex >> numberOfNeighbors;
        for (int j = 0; j < numberOfNeighbors; j++)
        {
            Neighbor neighbor;

            input >> neighbor.destination;

            // Temporary weights
            neighbor.weight = 1;

            graph.adjacencyList[vertex].push_back(neighbor);
        }
    }
}

void printGraph(const Graph &graph)
{
    cout << "Adjacency List\n\n";
    for (int i = 0; i < graph.vertices; i++)
    {
        cout << i << " : ";
        for (const Neighbor &neighbor : graph.adjacencyList[i])
        {
            cout << "(" << neighbor.destination << ", " << neighbor.weight << ") ";
        }
        cout << '\n';
    }
}