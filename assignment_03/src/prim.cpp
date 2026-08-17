#include "../include/prim.h"

#include <functional>
#include <queue>
#include <vector>

MSTResult primMST(const CSR &csr)
{
    int vertices = csr.rowPtr.size() - 1;

    std::vector<bool> visited(vertices, false);

    using PQEdge = std::pair<int, std::pair<int, int>>;

    std::priority_queue<
        PQEdge,
        std::vector<PQEdge>,
        std::greater<PQEdge>>
        pq;

    MSTResult result;
    result.totalWeight = 0;

    visited[0] = true;

    for (int i = csr.rowPtr[0]; i < csr.rowPtr[1]; i++)
    {
        pq.push({csr.values[i], {0, csr.colIdx[i]}});
    }

    while (!pq.empty() && result.edges.size() < vertices - 1)
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

        for (int i = csr.rowPtr[v]; i < csr.rowPtr[v + 1]; i++)
        {
            int next = csr.colIdx[i];

            if (!visited[next])
                pq.push({csr.values[i], {v, next}});
        }
    }

    return result;
}