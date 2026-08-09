#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

const long long INF = 1000000000000LL;

void generateGraph(int vertices, const string &filename, unsigned int seed)
{
    mt19937 generator(seed);
    uniform_real_distribution<double> probability(0.0, 1.0);
    uniform_int_distribution<int> weightDistribution(1, 20);
    vector<vector<long long>> matrix(vertices, vector<long long>(vertices, INF));
    for (int i = 0; i < vertices; i++)
        matrix[i][i] = 0;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
                continue;
            if (probability(generator) < 0.35)
                matrix[i][j] = weightDistribution(generator);
        }
    }
    ofstream output(filename);
    if (!output.is_open())
    {
        cerr << "Error: Unable to create " << filename << '\n';
        return;
    }
    output << vertices << '\n';
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (matrix[i][j] == INF)
                output << "INF";
            else
                output << matrix[i][j];
            if (j < vertices - 1)
                output << ' ';
        }
        output << '\n';
    }
    output.close();
    cout << "Generated: " << filename << " | V = " << vertices << '\n';
}

int main()
{
    const string directory = "assignment_02/tests/floyd_warshall/";
    generateGraph(10, directory + "fw_10.txt", 2001);
    generateGraph(100, directory + "fw_100.txt", 2002);
    generateGraph(500, directory + "fw_500.txt", 2003);
    generateGraph(1000, directory + "fw_1000.txt", 2004);
    generateGraph(2000, directory + "fw_2000.txt", 2005);
    cout << "\nAll Floyd-Warshall test files generated successfully.\n";
    return 0;
}