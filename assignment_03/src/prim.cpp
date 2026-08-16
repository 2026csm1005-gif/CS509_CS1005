#include "../include/prim.h"

#include <queue>
#include <vector>
#include <functional>

MSTResult primMST(const MSTAdjListGraph &graph)
{
    std::vector<bool> visited(graph.V, false);

    using PQEdge = std::pair<int, std::pair<int, int>>;
    std::priority_queue<
        PQEdge,
        std::vector<PQEdge>,
        std::greater<PQEdge>>
        pq;

    MSTResult result;
    result.totalWeight = 0;

    visited[0] = true;

    for (const auto &nbr : graph.adj[0])
        pq.push({nbr.weight, {0, nbr.vertex}});

    while (!pq.empty() && result.edges.size() < graph.V - 1)
    {
        auto current = pq.top();
        pq.pop();

        int weight = current.first;
        int u = current.second.first;
        int v = current.second.second;

        if (visited[v])
            continue;

        visited[v] = true;

        result.edges.push_back({u, v, weight});
        result.totalWeight += weight;

        for (const auto &nbr : graph.adj[v])
        {
            if (!visited[nbr.vertex])
                pq.push({nbr.weight, {v, nbr.vertex}});
        }
    }

    return result;
}