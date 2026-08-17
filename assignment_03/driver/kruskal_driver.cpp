#include "../include/mst_graph_reader.h"
#include "../include/kruskal.h"
#include "../../assignment_01/include/timer.h"
#include "../../assignment_01/include/edge.h"
#include "../../assignment_01/include/csr.h"

#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: kruskal_driver <input_file>\n";
        return 1;
    }

    try
    {
        MSTAdjListGraph mstGraph = readMSTGraph(argv[1]);
        Graph graph = convertToGraph(mstGraph);

        std::vector<Edge> edgeList = createEdgeList(graph);
        CSR csr = createCSR(edgeList, graph.vertices);

        Timer timer;
        timer.start();
        MSTResult result = kruskalMST(csr);
        timer.stop();
        double time = timer.getElapsedTime();

        std::cout << "Algorithm: Kruskal's MST\n";
        std::cout << "MST edges:\n";

        if (graph.vertices <= 100)
        {
            for (const auto &edge : result.edges)
                std::cout << edge.u << " " << edge.v << " " << edge.weight << "\n";
        }
        else
        {
            std::cout << "(suppressed for large graph)\n";
        }

        std::cout << "Total MST weight: " << result.totalWeight << "\n";
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Execution time: " << time << " ms\n";
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }

    return 0;
}