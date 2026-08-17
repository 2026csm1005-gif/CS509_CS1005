#ifndef MST_GRAPH_READER_H
#define MST_GRAPH_READER_H

#include "../../assignment_01/include/graph.h"

#include <string>
#include <vector>

struct MSTNeighbor
{
    int vertex;
    int weight;
};

struct MSTAdjListGraph
{
    int V;
    int E;
    std::vector<std::vector<MSTNeighbor>> adj;
};

MSTAdjListGraph readMSTGraph(const std::string &filename);
Graph convertToGraph(const MSTAdjListGraph &mstGraph);

#endif