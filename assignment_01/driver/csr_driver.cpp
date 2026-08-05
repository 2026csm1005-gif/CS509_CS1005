#include <fstream>
#include <iostream>
#include "../include/edge.h"
#include "../include/csr.h"
#include "../include/graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: csr_driver <input_file>\n";
        return 1;
    }
    ifstream inputFile(argv[1]);
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
    CSR csr = createCSR(edgeList, graph.vertices);
    printCSR(csr);
    inputFile.close();
    return 0;
}