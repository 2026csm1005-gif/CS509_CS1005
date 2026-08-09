#include "../include/floyd_warshall.h"

#include <algorithm>
#include <limits>

using namespace std;

FloydWarshallResult floydWarshall(const vector<vector<long long>> &matrix)
{
    const long long INF = numeric_limits<long long>::max();
    FloydWarshallResult result; // making a copy.
    result.distance = matrix;
    result.negativeCycle = false;
    int vertices = static_cast<int>(result.distance.size());
    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            if (result.distance[i][k] == INF)
                continue;
            for (int j = 0; j < vertices; j++)
            {
                if (result.distance[k][j] == INF)
                    continue;
                long long throughK = result.distance[i][k] + result.distance[k][j];
                if (throughK < result.distance[i][j])
                    result.distance[i][j] = throughK;
            }
        }
    }
    for (int i = 0; i < vertices; i++)
    {
        if (result.distance[i][i] < 0)
        {
            result.negativeCycle = true;
            break;
        }
    }
    return result;
}