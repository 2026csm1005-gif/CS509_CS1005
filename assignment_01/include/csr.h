#ifndef CSR_H
#define CSR_H

#include <vector>
#include "edge.h"

struct CSR
{
    std::vector<int> rowPtr; // Offset Array
    std::vector<int> colIdx; // Intermediate Array
    std::vector<int> values; // Property Array
};

CSR createCSR(const std::vector<Edge> &edgeList, int vertices);
void printCSR(const CSR &csr);

#endif