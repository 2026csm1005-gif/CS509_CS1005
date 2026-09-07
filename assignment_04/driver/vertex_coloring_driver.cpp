#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../../assignment_01/include/csr.h"
#include "../../assignment_01/include/edge.h"
#include "../../assignment_01/include/graph.h"
#include "../../assignment_01/include/timer.h"
#include "../include/a4_graph_reader.h"
#include "../include/vertex_coloring.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0]
             << " <input_graph_file>\n";
        return 1;
    }

    const string filename = argv[1];

    Graph graph;
    string errorMessage;

    if (!readColoringGraph(filename, graph, errorMessage))
    {
        cerr << "Error: " << errorMessage << '\n';
        return 1;
    }

    vector<Edge> edgeList = createEdgeList(graph);
    CSR csr = createCSR(edgeList, graph.vertices);

    Timer timer;

    timer.start();

    ColoringResult result =
        greedyVertexColoring(graph.vertices, csr);

    timer.stop();

    cout << "\n=========================================\n";
    cout << "Welsh-Powell Vertex Coloring\n";
    cout << "=========================================\n";

    cout << "Input File: " << filename << '\n';
    cout << "Number of vertices: " << graph.vertices << '\n';
    cout << "Number of edges: " << graph.edges << '\n';

    if (graph.vertices <= 100)
    {
        cout << "\nVertex Colors:\n";

        for (int vertex = 0; vertex < graph.vertices; vertex++)
        {
            cout << "Vertex " << vertex
                 << " -> Color " << result.colors[vertex]
                 << '\n';
        }
    }
    else
    {
        cout << "\nVertex colors omitted for large graph.\n";
        cout << "Number of vertices is greater than 100.\n";
    }

    cout << "\nColors Used: "
         << result.colorsUsed << '\n';

    cout << "Coloring Valid: "
         << (result.valid ? "YES" : "NO") << '\n';

    cout << fixed << setprecision(6);

    cout << "Execution Time: "
         << timer.getElapsedTime()
         << " ms\n";

    cout << "=========================================\n";

    return result.valid ? 0 : 1;
}