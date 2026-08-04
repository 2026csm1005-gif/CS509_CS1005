#include "../include/edge.h"

#include <iostream>

using namespace std;

vector<Edge> createEdgeList(const Graph &graph)
{
    vector<Edge> edgeList;
    for (int source = 0; source < graph.vertices; source++)
    {
        for (const Neighbor &neighbor : graph.adjacencyList[source])
        {
            Edge edge;
            edge.source = source;
            edge.destination = neighbor.destination;
            edge.weight = neighbor.weight;
            edgeList.push_back(edge);
        }
    }
    return edgeList;
}

void printEdgeList(const vector<Edge> &edgeList)
{
    cout << "\nEdge List\n\n";
    for (const Edge &edge : edgeList)
    {
        cout << edge.source << " -> " << edge.destination << " (" << edge.weight << ")" << '\n';
    }
}