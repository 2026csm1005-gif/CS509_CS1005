#include "../include/mst_graph_reader.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: kruskal_driver <input_file>\n";
        return 1;
    }

    try
    {
        MSTAdjListGraph graph = readMSTGraph(argv[1]);

        std::cout << "Vertices: " << graph.V << "\n";
        std::cout << "Edges: " << graph.E << "\n";

        for (int u = 0; u < graph.V && u < 10; u++)
        {
            std::cout << u << ": ";
            for (auto &nbr : graph.adj[u])
                std::cout << "(" << nbr.vertex << "," << nbr.weight << ") ";
            std::cout << "\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << "\n";
        return 1;
    }

    return 0;
}