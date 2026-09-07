#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

struct DirectedEdge
{
    int source;
    int destination;
};

uint64_t makeKey(int source, int destination)
{
    return (static_cast<uint64_t>(static_cast<uint32_t>(source)) << 32) |
           static_cast<uint32_t>(destination);
}

void generateColoringGraph(int vertices, int edges, const string &filename)
{
    vector<vector<int>> adjacency(vertices);
    unordered_set<uint64_t> usedEdges;

    mt19937 generator(1000 + vertices);
    uniform_int_distribution<int> vertexDistribution(0, vertices - 1);

    for (int vertex = 1; vertex < vertices; vertex++)
    {
        int parent = vertexDistribution(generator) % vertex;

        int a = min(parent, vertex);
        int b = max(parent, vertex);

        uint64_t key = makeKey(a, b);
        usedEdges.insert(key);

        adjacency[a].push_back(b);
        adjacency[b].push_back(a);
    }

    while (static_cast<int>(usedEdges.size()) < edges)
    {
        int source = vertexDistribution(generator);
        int destination = vertexDistribution(generator);

        if (source == destination)
        {
            continue;
        }

        int a = min(source, destination);
        int b = max(source, destination);

        uint64_t key = makeKey(a, b);

        if (usedEdges.insert(key).second)
        {
            adjacency[a].push_back(b);
            adjacency[b].push_back(a);
        }
    }

    ofstream output(filename);

    if (!output)
    {
        cerr << "Error: Cannot create " << filename << '\n';
        return;
    }

    output << vertices << ' ' << edges << '\n';

    for (int vertex = 0; vertex < vertices; vertex++)
    {
        sort(adjacency[vertex].begin(), adjacency[vertex].end());

        output << vertex << ' ' << adjacency[vertex].size();

        for (int neighbor : adjacency[vertex])
        {
            output << ' ' << neighbor;
        }

        output << '\n';
    }

    output.close();

    cout << "Generated coloring graph: "
         << filename
         << " | V = " << vertices
         << " | E = " << edges << '\n';
}

void generatePageRankGraph(int vertices, int edges, const string &filename)
{
    vector<vector<int>> adjacency(vertices);
    unordered_set<uint64_t> usedEdges;

    mt19937 generator(2000 + vertices);
    uniform_int_distribution<int> vertexDistribution(0, vertices - 1);

    while (static_cast<int>(usedEdges.size()) < edges)
    {
        int source = vertexDistribution(generator);
        int destination = vertexDistribution(generator);

        if (source == destination)
        {
            continue;
        }

        uint64_t key = makeKey(source, destination);

        if (usedEdges.insert(key).second)
        {
            adjacency[source].push_back(destination);
        }
    }

    ofstream output(filename);

    if (!output)
    {
        cerr << "Error: Cannot create " << filename << '\n';
        return;
    }

    output << vertices << ' ' << edges << '\n';

    for (int vertex = 0; vertex < vertices; vertex++)
    {
        sort(adjacency[vertex].begin(), adjacency[vertex].end());

        output << vertex << ' ' << adjacency[vertex].size();

        for (int neighbor : adjacency[vertex])
        {
            output << ' ' << neighbor;
        }

        output << '\n';
    }

    output << "DAMPING 0.85\n";
    output << "TOLERANCE 0.000001\n";
    output << "MAX_ITERATIONS 100\n";

    output.close();

    cout << "Generated PageRank graph: "
         << filename
         << " | V = " << vertices
         << " | E = " << edges << '\n';
}

int main()
{
    fs::create_directories("assignment_04/tests/coloring");
    fs::create_directories("assignment_04/tests/pagerank");

    vector<pair<int, int>> coloringTests =
        {
            {10, 14},
            {100, 250},
            {10000, 30000},
            {50000, 150000},
            {100000, 300000}};

    vector<pair<int, int>> pageRankTests =
        {
            {10, 14},
            {100, 250},
            {1000, 3000},
            {10000, 30000},
            {50000, 150000}};

    cout << "\n=========================================\n";
    cout << "Assignment 4 Test Generator\n";
    cout << "=========================================\n\n";

    for (const auto &[vertices, edges] : coloringTests)
    {
        string filename =
            "assignment_04/tests/coloring/color_" +
            to_string(vertices) +
            ".txt";

        generateColoringGraph(vertices, edges, filename);
    }

    cout << '\n';

    for (const auto &[vertices, edges] : pageRankTests)
    {
        string filename =
            "assignment_04/tests/pagerank/pagerank_" +
            to_string(vertices) +
            ".txt";

        generatePageRankGraph(vertices, edges, filename);
    }

    cout << "\n=========================================\n";
    cout << "All Assignment 4 test files generated.\n";
    cout << "=========================================\n";

    return 0;
}