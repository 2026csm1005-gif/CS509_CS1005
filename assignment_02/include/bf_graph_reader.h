#ifndef BF_GRAPH_READER_H
#define BF_GRAPH_READER_H

#include <istream>
#include "../../assignment_01/include/graph.h"

bool readBellmanFordGraph(std::istream &input, Graph &graph, int &source);

#endif