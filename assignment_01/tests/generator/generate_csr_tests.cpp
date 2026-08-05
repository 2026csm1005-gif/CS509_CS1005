#include <fstream>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

void generateUndirectedGraph(const string &fileName, int vertices, int neighboursPerVertex)
{
    vector<set<int>> adjacency(vertices);
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 1; j <= neighboursPerVertex; j++)
        {
            int neighbour = (i + j) % vertices;
            adjacency[i].insert(neighbour);
            adjacency[neighbour].insert(i);
        }
    }
    int edgeCount = 0;
    for (const auto &neighbors : adjacency)
        edgeCount += neighbors.size();

    edgeCount /= 2;
    ofstream file(fileName);
    file << vertices << " " << edgeCount << "\n";
    for (int i = 0; i < vertices; i++)
    {
        file << i << " " << adjacency[i].size() << " ";
        for (int neighbor : adjacency[i])
            file << neighbor << " ";
        file << "\n";
    }
    file.close();
    cout << fileName << " generated successfully.\n";
}

int main()
{
    generateUndirectedGraph("tests/csr/csr_test_09.txt", 1000, 10);
    generateUndirectedGraph("tests/csr/csr_test_010.txt", 2500, 3);
    return 0;
}