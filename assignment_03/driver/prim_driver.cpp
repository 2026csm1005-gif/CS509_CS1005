#include "../include/mst_graph_reader.h"
#include "../include/prim.h"
#include "../../assignment_01/include/timer.h"

#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: prim_driver <input_file>\n";
        return 1;
    }

    try
    {
        MSTAdjListGraph graph = readMSTGraph(argv[1]);

        Timer timer;
        timer.start();
        MSTResult result = primMST(graph);
        timer.stop();
        double time = timer.getElapsedTime();

        std::cout << "Algorithm: Prim's MST\n";
        std::cout << "MST edges:\n";

        for (const auto &edge : result.edges)
            std::cout << edge.u << " " << edge.v << " " << edge.weight << "\n";

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