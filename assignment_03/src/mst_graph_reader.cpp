#include "../include/mst_graph_reader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

MSTAdjListGraph readMSTGraph(const std::string &filename)
{
    std::ifstream fin(filename);

    if (!fin.is_open())
        throw std::runtime_error("Error: Cannot open input file.");

    MSTAdjListGraph graph;

    fin >> graph.V >> graph.E;

    if (graph.V <= 0 || graph.E < 0)
        throw std::runtime_error("Error: Invalid graph size.");

    graph.adj.resize(graph.V);

    for (int i = 0; i < graph.V; i++)
    {
        int u, degree;
        fin >> u >> degree;

        if (u < 0 || u >= graph.V || degree < 0)
            throw std::runtime_error("Error: Invalid adjacency list entry.");

        for (int j = 0; j < degree; j++)
        {
            int v, w;
            fin >> v >> w;

            if (v < 0 || v >= graph.V)
                throw std::runtime_error("Error: Invalid neighbour vertex.");

            graph.adj[u].push_back({v, w});
        }
    }

    return graph;
}