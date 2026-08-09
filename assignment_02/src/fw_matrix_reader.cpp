#include "../include/fw_matrix_reader.h"
#include <limits>
#include <string>

using namespace std;

bool readFloydWarshallMatrix(istream &input, vector<vector<long long>> &matrix)
{
    int vertices;
    if (!(input >> vertices) || (vertices <= 0))
        return false;
    matrix.assign(vertices, vector<long long>(vertices));
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            string value;
            if (!(input >> value))
                return false;
            if (value == "INF")
                matrix[i][j] = numeric_limits<long long>::max();
            else
            {
                try
                {
                    matrix[i][j] = stoll(value);
                }
                catch (...)
                {
                    return false;
                }
            }
        }
    }
    return true;
}