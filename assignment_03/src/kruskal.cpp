#include "../include/kruskal.h"
#include "../include/dsu.h"

#include <algorithm>

MSTResult kruskalMST(const MSTAdjListGraph &graph)
{
    std::vector<MSTEdge> edgeList;

    // Build edge list (avoid duplicates)
    for (int u = 0; u < graph.V; u++)
    {
        for (const auto &nbr : graph.adj[u])
        {
            if (u < nbr.vertex)
            {
                edgeList.push_back({u, nbr.vertex, nbr.weight});
            }
        }
    }

    // Sort by weight
    std::sort(edgeList.begin(), edgeList.end(),
              [](const MSTEdge &a, const MSTEdge &b)
              {
                  return a.weight < b.weight;
              });

    DSU dsu(graph.V);
    MSTResult result;
    result.totalWeight = 0;

    for (const auto &edge : edgeList)
    {
        if (dsu.unite(edge.u, edge.v))
        {
            result.edges.push_back(edge);
            result.totalWeight += edge.weight;

            if (result.edges.size() == graph.V - 1)
                break;
        }
    }

    return result;
}