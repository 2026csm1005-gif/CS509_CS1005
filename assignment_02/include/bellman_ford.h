#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "../../assignment_01/include/csr.h"
#include <vector>

struct BellmanFordResult
{
    std::vector<int> distance;
    bool negativeCycle;
};

BellmanFordResult bellmanFord(const CSR &csr, int vertices, int source);

#endif