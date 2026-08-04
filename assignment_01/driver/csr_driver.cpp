#include <fstream>
#include <iostream>
#include "../include/edge.h"

#include "../include/graph.h"

using namespace std;

int main()
{
    ifstream inputFile("tests/csr/csr_test_01.txt");
    if (!inputFile.is_open())
    {
        cout << "Unable to open file.\n";
        return 1;
    }
    Graph graph;
    readGraph(inputFile, graph);
    printGraph(graph);
    vector<Edge> edgeList = createEdgeList(graph);
    printEdgeList(edgeList);
    inputFile.close();
    return 0;
}