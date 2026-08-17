# CS509 Assignment 3

## Overview

This assignment implements Minimum Spanning Tree (MST) algorithms for weighted undirected graphs.

Implemented algorithms:

- Kruskal's Algorithm
- Prim's Algorithm

Both algorithms use the same input graph, reuse the CSR implementation from Assignment 1 and report only algorithm execution time.

---

## Folder Structure

```
assignment_03/
│── driver/
│   ├── kruskal_driver.cpp
│   └── prim_driver.cpp
│
│── include/
│   ├── dsu.h
│   ├── kruskal.h
│   ├── mst_graph_reader.h
│   └── prim.h
│
│── src/
│   ├── dsu.cpp
│   ├── kruskal.cpp
│   ├── mst_graph_reader.cpp
│   └── prim.cpp
│
│── tests/
│   └── mst/
│       ├── mst_10.txt
│       ├── mst_100.txt
│       ├── mst_10000.txt
│       ├── mst_50000.txt
│       └── mst_100000.txt
│
└── utilities/
    └── generate_mst_tests.cpp
```

---

## Algorithms

### Kruskal's Algorithm

- Builds an edge list from the CSR graph.
- Sorts edges by weight.
- Uses Disjoint Set Union (Union-Find) with path compression and union by rank.
- Selects `V-1` edges without creating cycles.

### Prim's Algorithm

- Starts from vertex `0`.
- Uses a min-priority queue.
- Expands the tree by selecting the minimum-weight outgoing edge.
- Produces the same total MST weight as Kruskal.

---

## Compilation

### Kruskal

```bash
g++ assignment_03/driver/kruskal_driver.cpp \
assignment_03/src/kruskal.cpp \
assignment_03/src/dsu.cpp \
assignment_03/src/mst_graph_reader.cpp \
assignment_01/src/csr.cpp \
assignment_01/src/graph.cpp \
assignment_01/src/edge.cpp \
assignment_01/src/timer.cpp \
-o kruskal_driver.exe
```

### Prim

```bash
g++ assignment_03/driver/prim_driver.cpp \
assignment_03/src/prim.cpp \
assignment_03/src/mst_graph_reader.cpp \
assignment_01/src/csr.cpp \
assignment_01/src/graph.cpp \
assignment_01/src/edge.cpp \
assignment_01/src/timer.cpp \
-o prim_driver.exe
```

### MST Test Generator

```bash
g++ -std=c++17 assignment_03/utilities/generate_mst_tests.cpp \
-o generate_mst_tests.exe
```

---

## Running

Generate test files:

```bash
generate_mst_tests.exe
```

Run Kruskal:

```bash
kruskal_driver.exe assignment_03/tests/mst/mst_100.txt
```

Run Prim:

```bash
prim_driver.exe assignment_03/tests/mst/mst_100.txt
```

---

## Test Cases

Generated graph sizes:

| File           | Vertices |  Edges |
| -------------- | -------: | -----: |
| mst_10.txt     |       10 |     20 |
| mst_100.txt    |      100 |    300 |
| mst_10000.txt  |    10000 |  30000 |
| mst_50000.txt  |    50000 | 150000 |
| mst_100000.txt |   100000 | 300000 |

All generated graphs are connected, weighted, undirected and sparse.

---

## Output

For small graphs (`V ≤ 100`):

- MST edges
- Total MST weight
- Execution time

For larger graphs:

- MST edges suppressed
- Total MST weight
- Execution time

Execution time is printed with six decimal places.

---

## Results

| File           |      V |      E | Kruskal Wt. | Prim Wt. | Kruskal Time | Prim Time | Equal? | Status |
| -------------- | -----: | -----: | ----------: | -------: | -----------: | --------: | :----: | :----: |
| mst_10.txt     |     10 |     20 |         119 |      119 |     0.000000 ms |  0.000000 ms |  Yes   |  Pass  |
| mst_100.txt    |    100 |    300 |    1996 | 1996 |     0.000000 ms |  0.991000 ms |  Yes   |  Pass  |
| mst_10000.txt  |  10000 |  30000 |    202789 | 202789 |     13.245000 ms |  132.410000 ms |  Yes   |  Pass  |
| mst_50000.txt  |  50000 | 150000 |    1013724 | 1013724 |     70.049000 ms |  300.876000 ms |  Yes   |  Pass  |
| mst_100000.txt | 100000 | 300000 |    2021442 | 2021442 |     147.927000 ms |  688.085000 ms |  Yes   |  Pass  |

