#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>

#include "../../assignment_01/include/csr.h"

struct PageRankResult
{
    std::vector<double> ranks;
    int iterations;
    bool converged;
};

PageRankResult pageRank(
    int numVertices,
    const CSR &csr,
    double damping,
    double tolerance,
    int maxIterations);

#endif