#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include <filesystem>

struct Edge
{
    int u, v, w;
};

void generateGraph(const std::string &filename, int V, int E)
{
    std::mt19937 rng(42); // fixed seed for reproducibility
    std::uniform_int_distribution<int> weightDist(1, 100);

    std::set<std::pair<int, int>> usedEdges;
    std::vector<Edge> edges;

    // Step 1: Create a spanning tree to guarantee connectivity
    for (int v = 1; v < V; v++)
    {
        std::uniform_int_distribution<int> parentDist(0, v - 1);
        int u = parentDist(rng);

        usedEdges.insert({std::min(u, v), std::max(u, v)});
        edges.push_back({u, v, weightDist(rng)});
    }

    // Step 2: Add random edges until reaching E
    std::uniform_int_distribution<int> vertexDist(0, V - 1);

    while ((int)edges.size() < E)
    {
        int u = vertexDist(rng);
        int v = vertexDist(rng);

        if (u == v)
            continue;

        auto p = std::make_pair(std::min(u, v), std::max(u, v));

        if (usedEdges.count(p))
            continue;

        usedEdges.insert(p);
        edges.push_back({u, v, weightDist(rng)});
    }

    // Build adjacency list
    std::vector<std::vector<std::pair<int, int>>> adj(V);

    for (const auto &e : edges)
    {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w});
    }

    // Write file
    std::ofstream fout(filename);

    fout << V << " " << E << "\n";

    for (int u = 0; u < V; u++)
    {
        fout << u << " " << adj[u].size();

        for (const auto &nbr : adj[u])
            fout << " " << nbr.first << " " << nbr.second;

        fout << "\n";
    }

    fout.close();
}

int main()
{
    std::filesystem::create_directories("assignment_03/tests/mst");

    generateGraph("assignment_03/tests/mst/mst_10.txt", 10, 20);
    generateGraph("assignment_03/tests/mst/mst_100.txt", 100, 300);
    generateGraph("assignment_03/tests/mst/mst_10000.txt", 10000, 30000);
    generateGraph("assignment_03/tests/mst/mst_50000.txt", 50000, 150000);
    generateGraph("assignment_03/tests/mst/mst_100000.txt", 100000, 300000);

    std::cout << "All MST test files generated successfully.\n";
    return 0;
}