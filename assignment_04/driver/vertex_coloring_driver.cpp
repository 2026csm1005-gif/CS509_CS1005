#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../include/a4_graph_reader.h"
#include "../include/vertex_coloring.h"

#include "../../assignment_01/include/edge.h"
#include "../../assignment_01/include/csr.h"
#include "../../assignment_01/include/timer.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: vertex_coloring_driver <input_file>\n";
        return 1;
    }

    Graph graph;
    string errorMessage;

    if (!readColoringGraph(
            argv[1],
            graph,
            errorMessage))
    {
        cerr << "Error: " << errorMessage << '\n';
        return 1;
    }

    // Preprocessing: not timed.
    vector<Edge> edgeList =
        createEdgeList(graph);

    CSR csr =
        createCSR(
            edgeList,
            graph.vertices);

    Timer timer;

    // Start timing ONLY before algorithm.
    timer.start();

    ColoringResult result =
        greedyVertexColoring(
            graph.vertices,
            csr);

    timer.stop();

    cout << "\n=========================================\n";
    cout << "Greedy Vertex Coloring\n";
    cout << "=========================================\n";

    cout << "Vertices: "
         << graph.vertices << '\n';

    cout << "Edges: "
         << graph.edges << '\n';

    cout << "\nVertex colors:\n";

    for (int vertex = 0;
         vertex < graph.vertices;
         ++vertex)
    {
        cout << vertex
             << " "
             << result.colors[vertex]
             << '\n';
    }

    cout << "\nColors used: "
         << result.colorsUsed
         << '\n';

    cout << "Valid coloring: "
         << (result.valid ? "Yes" : "No")
         << '\n';

    cout << fixed
         << setprecision(6);

    cout << "Execution time: "
         << timer.getElapsedTime()
         << " ms\n";

    cout << "=========================================\n";

    return result.valid ? 0 : 1;
}