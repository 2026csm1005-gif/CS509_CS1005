#include <iostream>
#include <fstream>
#include <random>
#include <set>
#include <vector>
#include <string>

using namespace std;

struct Edge
{
    int u;
    int v;
    int weight;
};

void generateTest(int V, int E, const string &filename)
{
    ofstream out(filename);

    if (!out)
    {
        cerr << "Error opening " << filename << endl;
        return;
    }

    vector<vector<pair<int, int>>> adj(V);
    set<pair<int, int>> edges;

    mt19937 rng(42 + V);
    uniform_int_distribution<int> weightDist(1, 100);

    // --------------------------------------------------
    // Step 1: Create a connected spanning tree
    // --------------------------------------------------
    for (int v = 1; v < V; ++v)
    {
        uniform_int_distribution<int> parentDist(0, v - 1);

        int u = parentDist(rng);
        int w = weightDist(rng);

        edges.insert({min(u, v), max(u, v)});

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // --------------------------------------------------
    // Step 2: Add random edges until E is reached
    // --------------------------------------------------
    uniform_int_distribution<int> vertexDist(0, V - 1);

    while (static_cast<int>(edges.size()) < E)
    {
        int u = vertexDist(rng);
        int v = vertexDist(rng);

        if (u == v)
            continue;

        int a = min(u, v);
        int b = max(u, v);

        if (edges.insert({a, b}).second)
        {
            int w = weightDist(rng);

            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
    }

    // --------------------------------------------------
    // Step 3: Write graph in the format expected by
    // mst_graph_reader.cpp
    // --------------------------------------------------
    out << V << " " << E << "\n";

    for (int u = 0; u < V; ++u)
    {
        out << u << " " << adj[u].size();

        for (const auto &[v, w] : adj[u])
        {
            out << " " << v << " " << w;
        }

        out << "\n";
    }

    out.close();

    cout << "Generated " << filename
         << " | V = " << V
         << " | E = " << E << endl;
}

int main()
{
    generateTest(10, 20, "tests/mst/mst_10.txt");
    generateTest(100, 300, "tests/mst/mst_100.txt");
    generateTest(10000, 30000, "tests/mst/mst_10000.txt");
    generateTest(50000, 150000, "tests/mst/mst_50000.txt");
    generateTest(100000, 300000, "tests/mst/mst_100000.txt");

    cout << "\nAll MST test cases generated successfully.\n";

    return 0;
}