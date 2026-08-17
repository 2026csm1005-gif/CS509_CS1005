#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "mst_graph_reader.h"
#include "../../assignment_01/include/csr.h"
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

MSTResult kruskalMST(const CSR &csr);

#endif