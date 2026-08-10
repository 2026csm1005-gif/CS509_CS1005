#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "../include/bellman_ford.h"
#include "../include/floyd_warshall.h"
#include "../include/fw_matrix_reader.h"

using namespace std;

const long long INF = numeric_limits<long long>::max();

bool compareDistances(const vector<long long> &bfDistance, const vector<long long> &fwRow)
{
    if (bfDistance.size() != fwRow.size())
        return false;
    for (size_t i = 0; i < bfDistance.size(); i++)
    {
        if (bfDistance[i] != fwRow[i])
            return false;
    }
    return true;
}
bool runCrossCheck(const string &filename)
{
    ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open file: " << filename << '\n';
        return false;
    }
    vector<vector<long long>> matrix;
    if (!readFloydWarshallMatrix(inputFile, matrix))
    {
        cerr << "Error: Invalid Floyd-Warshall input file.\n";
        return false;
    }
    inputFile.close();
    int vertices = static_cast<int>(matrix.size());
    FloydWarshallResult fwResult = floydWarshall(matrix); // Running Floyd-Warshall once.
    if (fwResult.negativeCycle)
    {
        cerr << "Error: Cross-check graph contains a negative cycle.\n";
        return false;
    }
    cout << "\n=========================================\n";
    cout << "Bellman-Ford vs Floyd-Warshall Cross-Check\n";
    cout << "=========================================\n";
    cout << "Test file      : " << filename << '\n';
    cout << "Vertices       : " << vertices << '\n';
    cout << "Sources checked: " << vertices << '\n';
    int mismatches = 0;
    for (int source = 0; source < vertices; source++) // Running Bellman-Ford from every vertex.
    {
        vector<long long> bfDistance(vertices, INF);
        bfDistance[source] = 0;
        for (int iteration = 0; iteration < vertices - 1; iteration++)
        {
            bool changed = false;
            for (int u = 0; u < vertices; u++)
            {
                if (bfDistance[u] == INF)
                    continue;
                for (int v = 0; v < vertices; v++)
                {
                    if (matrix[u][v] == INF)
                        continue;
                    long long newDistance = bfDistance[u] + matrix[u][v];
                    if (newDistance < bfDistance[v])
                    {
                        bfDistance[v] = newDistance;
                        changed = true;
                    }
                }
            }
            if (!changed)
            {
                break;
            }
        }
        if (!compareDistances(bfDistance, fwResult.distance[source]))
        {
            mismatches++;
            cout << "Mismatch found for source: " << source << '\n';
        }
    }
    cout << "Mismatches      : " << mismatches << '\n';
    if (mismatches == 0)
        cout << "Result          : PASS\n";
    else
        cout << "Result          : FAIL\n";
    cout << "=========================================\n";
    return (mismatches == 0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: cross_check_bf_fw <floyd_warshall_test_file>\n";
        return 1;
    }
    if (runCrossCheck(argv[1]))
        return 0;
    else
        return 1;
}