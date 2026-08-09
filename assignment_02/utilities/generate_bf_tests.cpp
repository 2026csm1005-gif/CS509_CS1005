#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
};
void generateGraph(int vertices, int edges, const string &filename, unsigned int seed)
{
    vector<vector<pair<int, int>>> adjacency(vertices);
    mt19937 generator(seed);
    for (int i = 0; i < vertices - 1; i++)
    {
        adjacency[i].push_back({i + 1, 1});
    }
    int currentEdges = vertices - 1;
    uniform_int_distribution<int> vertexDistribution(0, vertices - 1);
    uniform_int_distribution<int> weightDistribution(1, 20);
    while (currentEdges < edges)
    {
        int source = vertexDistribution(generator);
        int destination = vertexDistribution(generator);
        if (source == destination)
            continue;
        int weight = weightDistribution(generator);
        adjacency[source].push_back({destination, weight});
        currentEdges++;
    }
    ofstream output(filename);
    if (!output.is_open())
    {
        cerr << "Error: Unable to create " << filename << '\n';
        return;
    }
    output << vertices << ' ' << edges << '\n';
    for (int vertex = 0; vertex < vertices; vertex++)
    {
        output << vertex << ' ' << adjacency[vertex].size();
        for (const auto &neighbor : adjacency[vertex])
        {
            output << ' ' << neighbor.first << ' ' << neighbor.second;
        }
        output << '\n';
    }
    output << "SOURCE 0\n";
    output.close();
    cout << "Generated: " << filename << " | V = " << vertices << " | E = " << edges << '\n';
}

int main()
{
    const string directory = "assignment_02/tests/bellman_ford/";
    // generateGraph(10, 20, directory + "bf_10.txt", 1001);        Since Adding Manually.
    generateGraph(100, 300, directory + "bf_100.txt", 1002);
    generateGraph(10000, 30000, directory + "bf_10000.txt", 1003);
    generateGraph(50000, 150000, directory + "bf_50000.txt", 1004);
    generateGraph(100000, 300000, directory + "bf_100000.txt", 1005);
    cout << "\nAll Bellman-Ford test files generated successfully.\n";
    return 0;
}