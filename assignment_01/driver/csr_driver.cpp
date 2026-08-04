#include <fstream>
#include <iostream>

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

    inputFile.close();

    return 0;
}