#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H

#include <vector>

#include "../../assignment_01/include/csr.h"

struct ColoringResult
{
    std::vector<int> colors;
    int colorsUsed;
    bool valid;
};

ColoringResult greedyVertexColoring(
    int numVertices,
    const CSR &csr);

bool validateColoring(
    int numVertices,
    const CSR &csr,
    const std::vector<int> &colors);

#endif