#ifndef A4_GRAPH_READER_H
#define A4_GRAPH_READER_H

#include <string>
#include "../../assignment_01/include/graph.h"

bool readColoringGraph(
    const std::string &filename,
    Graph &graph,
    std::string &errorMessage);

bool readPageRankGraph(
    const std::string &filename,
    Graph &graph,
    double &damping,
    double &tolerance,
    int &maxIterations,
    std::string &errorMessage);

#endif