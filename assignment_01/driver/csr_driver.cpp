#include <fstream>
#include <iostream>
#include <iomanip>
#include "../include/edge.h"
#include "../include/csr.h"
#include "../include/graph.h"
#include "../include/timer.h"

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
    cout << "\n";
    cout << "=========================================\n";
    cout << "CSR Graph Conversion\n";
    cout << "=========================================\n\n";
    Graph graph;
    readGraph(inputFile, graph);
    // printGraph(graph);
    vector<Edge> edgeList = createEdgeList(graph);
    // printEdgeList(edgeList);
    Timer timer;
    timer.start();
    CSR csr = createCSR(edgeList, graph.vertices);
    timer.stop();
    if (graph.vertices <= 10)
    {
        printGraph(graph);
        printEdgeList(edgeList);
        printCSR(csr);
    }
    else
    {
        cout << "Graph too large to display!" << '\n';
    }
    cout << fixed << setprecision(6);
    cout << "CSR Conversion Time : " << timer.getElapsedTime() << " ms" << '\n';
    inputFile.close();
    cout << "\n=========================================\n";
    cout << "CSR Conversion Completed Successfully\n";
    cout << "=========================================\n";
    return 0;
}