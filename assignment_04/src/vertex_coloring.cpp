#include "../include/vertex_coloring.h"

#include <algorithm>
#include <vector>

using namespace std;

ColoringResult greedyVertexColoring(
    int numVertices,
    const CSR &csr)
{
    ColoringResult result;

    result.colors.assign(numVertices, -1);
    result.colorsUsed = 0;
    result.valid = false;

    // Degree comes directly from CSR.
    vector<int> degree(numVertices);

    for (int vertex = 0;
         vertex < numVertices;
         ++vertex)
    {
        degree[vertex] =
            csr.rowPtr[vertex + 1] -
            csr.rowPtr[vertex];
    }

    // Welsh-Powell ordering.
    vector<int> order(numVertices);

    for (int vertex = 0;
         vertex < numVertices;
         ++vertex)
    {
        order[vertex] = vertex;
    }

    sort(
        order.begin(),
        order.end(),
        [&degree](int a, int b)
        {
            if (degree[a] != degree[b])
                return degree[a] > degree[b];

            // Deterministic tie-breaking.
            return a < b;
        });

    // At most V colors are ever required.
    vector<bool> usedColor(
        numVertices,
        false);

    for (int vertex : order)
    {
        fill(
            usedColor.begin(),
            usedColor.end(),
            false);

        // Mark colors already used by neighbours.
        for (int index = csr.rowPtr[vertex];
             index < csr.rowPtr[vertex + 1];
             ++index)
        {
            int neighbour =
                csr.colIdx[index];

            if (result.colors[neighbour] != -1)
            {
                usedColor[result.colors[neighbour]] = true;
            }
        }

        // Select smallest available color.
        int color = 0;

        while (color < numVertices &&
               usedColor[color])
        {
            ++color;
        }

        result.colors[vertex] = color;

        result.colorsUsed =
            max(
                result.colorsUsed,
                color + 1);
    }

    result.valid =
        validateColoring(
            numVertices,
            csr,
            result.colors);

    return result;
}

bool validateColoring(
    int numVertices,
    const CSR &csr,
    const vector<int> &colors)
{
    if (static_cast<int>(colors.size()) != numVertices)
        return false;

    for (int vertex = 0;
         vertex < numVertices;
         ++vertex)
    {
        if (colors[vertex] < 0)
            return false;

        for (int index = csr.rowPtr[vertex];
             index < csr.rowPtr[vertex + 1];
             ++index)
        {
            int neighbour =
                csr.colIdx[index];

            if (neighbour < 0 ||
                neighbour >= numVertices)
            {
                return false;
            }

            if (colors[vertex] ==
                colors[neighbour])
            {
                return false;
            }
        }
    }

    return true;
}