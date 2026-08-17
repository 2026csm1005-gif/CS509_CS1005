#include "../include/kruskal.h"
#include "../include/dsu.h"

#include <algorithm>

MSTResult kruskalMST(const CSR &csr)
{
    std::vector<MSTEdge> edgeList;

    int vertices = csr.rowPtr.size() - 1;

    for (int u = 0; u < vertices; u++)
    {
        for (int i = csr.rowPtr[u]; i < csr.rowPtr[u + 1]; i++)
        {
            int v = csr.colIdx[i];
            int w = csr.values[i];

            if (u < v)
                edgeList.push_back({u, v, w});
        }
    }

    std::sort(edgeList.begin(), edgeList.end(),
              [](const MSTEdge &a, const MSTEdge &b)
              {
                  return a.weight < b.weight;
              });

    DSU dsu(vertices);
    MSTResult result;
    result.totalWeight = 0;

    for (const auto &edge : edgeList)
    {
        if (dsu.unite(edge.u, edge.v))
        {
            result.edges.push_back(edge);
            result.totalWeight += edge.weight;

            if (result.edges.size() == vertices - 1)
                break;
        }
    }

    return result;
}