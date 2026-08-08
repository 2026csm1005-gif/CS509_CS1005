#include "../include/bellman_ford.h"

#include <limits>

using namespace std;

BellmanFordResult bellmanFord(const CSR &csr, int vertices, int source)
{
    const int INF = numeric_limits<int>::max();
    BellmanFordResult result;
    result.distance.assign(vertices, INF);
    result.negativeCycle = false;
    result.distance[source] = 0;
    for (int i = 0; i < vertices - 1; i++) // Relax all edges (V-1) times.
    {
        bool updated = false;
        for (int u = 0; u < vertices; u++)
        {
            if (result.distance[u] == INF) // Skip those vertices not reachable from source.
                continue;
            int start = csr.rowPtr[u];
            int end = csr.rowPtr[u + 1];
            for (int index = start; index < end; index++)
            {
                int v = csr.colIdx[index];
                int weight = csr.values[index];
                if (result.distance[u] != INF && result.distance[u] + weight < result.distance[v])
                {
                    result.distance[v] = result.distance[u] + weight;
                    updated = true;
                }
            }
        }
        if (!updated) // If no distance changed during a complete pass, further relaxation not required.
            break;
    }
    for (int u = 0; u < vertices; u++) // Negative-cycle detection.
    {
        if (result.distance[u] == INF)
            continue;
        int start = csr.rowPtr[u];
        int end = csr.rowPtr[u + 1];
        for (int index = start; index < end; index++)
        {
            int v = csr.colIdx[index];
            int weight = csr.values[index];
            if (result.distance[u] + weight < result.distance[v])
            {
                result.negativeCycle = true;
                return result;
            }
        }
    }
    return result;
}