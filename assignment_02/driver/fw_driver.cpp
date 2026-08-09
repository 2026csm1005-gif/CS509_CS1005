#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#include "../../assignment_01/include/timer.h"
#include "../include/fw_matrix_reader.h"
#include "../include/floyd_warshall.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: fw_driver <input_file>\n";
        return 1;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open input file.\n";
        return 1;
    }
    vector<vector<long long>> matrix;
    if (!readFloydWarshallMatrix(inputFile, matrix))
    {
        cerr << "Error: Invalid Floyd-Warshall input file.\n";
        inputFile.close();
        return 1;
    }
    inputFile.close();
    int vertices = static_cast<int>(matrix.size());
    Timer timer;
    timer.start();
    FloydWarshallResult result = floydWarshall(matrix); // Running Floyd-Warshall.
    timer.stop();
    cout << "\n=========================================\n";
    cout << "Algorithm: Floyd-Warshall\n";
    cout << "Vertices : " << vertices << "\n";
    cout << "=========================================\n\n";
    if (result.negativeCycle) // Checking negative-cycle.
        cout << "Negative cycle: true\n";
    else
    {
        if (vertices <= 100)
        {
            cout << "Distance matrix:\n";
            for (int i = 0; i < vertices; i++)
            {
                for (int j = 0; j < vertices; j++)
                {
                    if (result.distance[i][j] == numeric_limits<long long>::max())
                        cout << setw(8) << "INF";
                    else
                        cout << setw(8) << result.distance[i][j];
                }
                cout << '\n';
            }
        }
        else
            cout << "Distance matrix: suppressed for large graph\n";
        cout << "\nNegative cycle: false\n";
    }
    cout << fixed << setprecision(6);
    cout << "Execution time: " << timer.getElapsedTime() << " ms\n";
    cout << "=========================================\n";
    return 0;
}