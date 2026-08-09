#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>

#include "../../assignment_01/include/edge.h"
#include "../../assignment_01/include/csr.h"
#include "../../assignment_01/include/timer.h"

#include "../include/bf_graph_reader.h"
#include "../include/bellman_ford.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: bf_driver <input_file>\n";
        return 1;
    }
    ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open input file.\n";
        return 1;
    }
    Graph graph;
    int source;
    if (!readBellmanFordGraph(inputFile, graph, source)) // Read weighted graph and source.
    {
        cerr << "Error: Invalid Bellman-Ford input file.\n";
        inputFile.close();
        return 1;
    }
    inputFile.close();
    vector<Edge> edgeList = createEdgeList(graph); // Convert graph to Edge List.
    CSR csr = createCSR(edgeList, graph.vertices); // Convert Edge List to CSR.

    Timer timer;
    timer.start();
    BellmanFordResult result = bellmanFord(csr, graph.vertices, source); // Running Bellman-Ford Algorithm.
    timer.stop();

    cout << "\n=========================================\n";
    cout << "Bellman-Ford Shortest Path\n";
    cout << "=========================================\n";
    cout << "Vertices : " << graph.vertices << '\n';
    cout << "Edges    : " << graph.edges << '\n';
    cout << "Source   : " << source << "\n\n";
    if (result.negativeCycle)
        cout << "Negative cycle: detected\n";
    else
    {
        if (graph.vertices <= 100) // Print complete distance table only for small test cases.
        {
            cout << left << setw(10) << "Vertex" << "Distance\n";
            cout << "-------------------------\n";
            for (int vertex = 0; vertex < graph.vertices; vertex++)
            {
                cout << left << setw(10) << vertex;
                if (result.distance[vertex] == numeric_limits<int>::max())
                    cout << "INF\n";
                else
                    cout << result.distance[vertex] << '\n';
            }
        }
        else
        {
            cout << "Distance table: suppressed for large graph\n";
        }
        cout << "\nNegative cycle: none\n";
    }
    cout << fixed << setprecision(6);
    cout << "\nBellman-Ford Execution Time : " << timer.getElapsedTime() << " ms\n";
    cout << "=========================================\n";
    return 0;
}