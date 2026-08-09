#include "../include/bf_graph_reader.h"

#include <string>

using namespace std;

bool readBellmanFordGraph(istream &input, Graph &graph, int &source)
{
    int vertices;
    int edges;
    if (!(input >> vertices >> edges))
        return false;
    if (vertices <= 0 || edges < 0)
        return false;
    graph.vertices = vertices;
    graph.edges = edges;
    graph.adjacencyList.clear();
    graph.adjacencyList.resize(vertices);
    for (int i = 0; i < vertices; i++)
    {
        int vertex;
        int numberOfNeighbors;
        if (!(input >> vertex >> numberOfNeighbors))
            return false;
        if (vertex < 0 || vertex >= vertices || numberOfNeighbors < 0)
            return false;
        for (int j = 0; j < numberOfNeighbors; j++)
        {
            Neighbor neighbor;
            if (!(input >> neighbor.destination >> neighbor.weight))
                return false;
            if (neighbor.destination < 0 || neighbor.destination >= vertices)
                return false;
            graph.adjacencyList[vertex].push_back(neighbor);
        }
    }
    string sourceLabel;
    if (!(input >> sourceLabel >> source) || (sourceLabel != "SOURCE") || (source < 0 || source >= vertices))
        return false;
    return true;
}