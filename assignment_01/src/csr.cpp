#include "../include/csr.h"

#include <iostream>

using namespace std;

CSR createCSR(const vector<Edge> &edgeList, int vertices)
{
    CSR csr;

    // rowPtr size = vertices + 1
    csr.rowPtr.resize(vertices + 1, 0);

    // Count outgoing edges of every vertex
    for (const Edge &edge : edgeList)
    {
        csr.rowPtr[edge.source + 1]++;
    }

    // Prefix sum
    for (int i = 1; i <= vertices; i++)
    {
        csr.rowPtr[i] += csr.rowPtr[i - 1];
    }

    csr.colIdx.resize(edgeList.size());
    csr.values.resize(edgeList.size());

    // Temporary copy of rowPtr
    vector<int> currentIndex = csr.rowPtr;

    // Fill CSR arrays
    for (const Edge &edge : edgeList)
    {
        int index = currentIndex[edge.source];
        csr.colIdx[index] = edge.destination;
        csr.values[index] = edge.weight;
        currentIndex[edge.source]++;
    }

    return csr;
}

void printCSR(const CSR &csr)
{
    cout << "\nCSR Representation\n\n";
    cout << "row_ptr : ";
    for (int value : csr.rowPtr)
    {
        cout << value << " ";
    }
    cout << "\n";

    cout << "col_idx : ";
    for (int value : csr.colIdx)
    {
        cout << value << " ";
    }
    cout << "\n";

    cout << "values  : ";
    for (int value : csr.values)
    {
        cout << value << " ";
    }
    cout << "\n";
}