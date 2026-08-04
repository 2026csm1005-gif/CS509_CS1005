#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include "graph.h"

struct Edge
{
    int source;
    int destination;
    int weight;
};

std::vector<Edge> createEdgeList(const Graph &graph);

void printEdgeList(const std::vector<Edge> &edgeList);

#endif