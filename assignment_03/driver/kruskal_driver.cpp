#include "../include/dsu.h"
#include <iostream>

int main()
{
    DSU dsu(5);

    dsu.unite(0, 1);
    dsu.unite(1, 2);

    std::cout << (dsu.find(0) == dsu.find(2)) << "\n";
    std::cout << (dsu.find(3) == dsu.find(4)) << "\n";

    return 0;
}