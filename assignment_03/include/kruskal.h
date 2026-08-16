#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "mst_graph_reader.h"
#include <vector>

struct MSTEdge
{
    int u;
    int v;
    int weight;
};

struct MSTResult
{
    std::vector<MSTEdge> edges;
    long long totalWeight;
};

MSTResult kruskalMST(const MSTAdjListGraph &graph);

#endif