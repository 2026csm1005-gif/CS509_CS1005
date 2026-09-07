#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "../include/a4_graph_reader.h"
#include "../include/pagerank.h"

#include "../../assignment_01/include/edge.h"
#include "../../assignment_01/include/csr.h"
#include "../../assignment_01/include/timer.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: pagerank_driver <input_file>\n";
        return 1;
    }

    Graph graph;

    double damping;
    double tolerance;
    int maxIterations;

    string errorMessage;

    if (!readPageRankGraph(
            argv[1],
            graph,
            damping,
            tolerance,
            maxIterations,
            errorMessage))
    {
        cerr << "Error: "
             << errorMessage
             << '\n';

        return 1;
    }

    vector<Edge> edgeList =
        createEdgeList(graph);

    CSR csr =
        createCSR(
            edgeList,
            graph.vertices);

    Timer timer;

    timer.start();

    PageRankResult result =
        pageRank(
            graph.vertices,
            csr,
            damping,
            tolerance,
            maxIterations);

    timer.stop();

    cout << "\n=========================================\n";
    cout << "PageRank\n";
    cout << "=========================================\n";

    cout << fixed
         << setprecision(6);

    cout << "Vertices: "
         << graph.vertices
         << '\n';

    cout << "Edges: "
         << graph.edges
         << '\n';

    cout << "Damping: "
         << damping
         << '\n';

    cout << "Tolerance: "
         << tolerance
         << '\n';

    cout << "Max iterations: "
         << maxIterations
         << '\n';

    cout << "\nVertex ranks:\n";

    double rankSum = 0.0;

    for (int vertex = 0;
         vertex < graph.vertices;
         ++vertex)
    {
        cout << vertex
             << " "
             << result.ranks[vertex]
             << '\n';

        rankSum += result.ranks[vertex];
    }

    cout << "\nSum of ranks: "
         << rankSum
         << '\n';

    cout << "Iterations: "
         << result.iterations
         << '\n';

    cout << "Converged: "
         << (result.converged ? "true" : "false")
         << '\n';

    cout << "Execution time: "
         << timer.getElapsedTime()
         << " ms\n";

    cout << "=========================================\n";

    return 0;
}