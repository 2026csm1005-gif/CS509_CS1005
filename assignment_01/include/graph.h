#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

struct Neighbor
{
    int destination;
    int weight;
};

struct Graph
{
    int vertices;
    int edges;

    std::vector<std::vector<Neighbor>> adjacencyList;
};

Graph createGraph(int vertices);

void readGraph(std::istream &input, Graph &graph);
void printGraph(const Graph &graph);

#endif