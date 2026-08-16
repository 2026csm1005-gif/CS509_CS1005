#include "../include/mst_graph_reader.h"
#include "../include/prim.h"

#include <iostream>

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
        MSTResult result = primMST(graph);

        std::cout << "Algorithm: Prim's MST\n";

        if (graph.V <= 100)
        {
            std::cout << "MST edges:\n";

            for (const auto &edge : result.edges)
            {
                std::cout << edge.u << " " << edge.v << " " << edge.weight << "\n";
            }
        }
        std::cout << "Total MST weight: " << result.totalWeight << "\n";
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }

    return 0;
}