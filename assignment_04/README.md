# CS509 – Assignment 4

## Overview

This assignment implements two graph algorithms:

1. **Greedy Vertex Coloring (Welsh–Powell Algorithm)**
2. **PageRank**

---

## Repository Structure

```text
assignment_04/
├── include/
│   ├── a4_graph_reader.h
│   ├── vertex_coloring.h
│   └── pagerank.h
│
├── src/
│   ├── a4_graph_reader.cpp
│   ├── vertex_coloring.cpp
│   └── pagerank.cpp
│
├── driver/
│   ├── vertex_coloring_driver.cpp
│   └── pagerank_driver.cpp
│
├── utilities/
│   └── generate_a4_tests.cpp
│
└── tests/
    ├── coloring/
    └── pagerank/
```

---

# 1. Greedy Vertex Coloring

The **Welsh–Powell algorithm** colors the vertices of an undirected graph using a greedy strategy.

### Algorithm

1. Calculate the degree of every vertex.
2. Sort vertices in non-increasing order of degree.
3. Start with the first vertex and assign the smallest available color.
4. Continue assigning the same color to vertices that are not adjacent to already colored vertices.
5. Repeat with the next unused color until all vertices are colored.
6. Validate the resulting coloring.

The implementation uses the CSR representation for efficient adjacency access.

### Output

For small graphs, the driver reports:

- Color of every vertex
- Number of colors used
- Coloring validity
- Execution time

For large graphs, individual vertex colors are omitted.

### Complexity

Let `V` be the number of vertices and `E` the number of edges.

- Degree calculation: `O(V)`
- Sorting vertices: `O(V log V)`
- Greedy coloring: `O(V + E)` with CSR adjacency traversal

Overall:

```text
O(V log V + E)
```

Space complexity:

```text
O(V + E)
```

---

# 2. PageRank

PageRank assigns an importance score to every vertex of a directed graph.

The implementation uses:

```text
PR(v) = (1-d)/N + d * Σ(PR(u) / outdegree(u))
```

where:

- `N` = number of vertices
- `d` = damping factor
- `u` = vertex having an outgoing edge to `v`

The default damping factor used in the test cases is:

```text
d = 0.85
```

### Algorithm

1. Initialize every vertex with rank `1/N`.
2. Calculate the new rank of every vertex using the ranks from the previous iteration.
3. Handle dangling vertices (vertices with zero outgoing edges) without division by zero.
4. Calculate the total change in PageRank values.
5. Stop when the change is less than or equal to the specified tolerance, or when the maximum number of iterations is reached.

Updates are performed simultaneously using the previous iteration's ranks.

### Output

The driver reports:

- PageRank of every vertex for small graphs
- Rank sum
- Number of iterations
- Convergence status
- Execution time

For large graphs, individual PageRank values are omitted.

The rank sum should be approximately:

```text
1.0
```

### Complexity

For `V` vertices, `E` edges, and `I` iterations:

```text
O(I(V + E))
```

Space complexity:

```text
O(V + E)
```

---

# Input Format

## Vertex Coloring

```text
V E
vertex degree neighbor1 neighbor2 ... neighbor_degree
...
```

The graph is undirected. Therefore, every edge must appear in both directions.

Example:

```text
4 4
0 2 1 3
1 2 0 2
2 2 1 3
3 2 0 2
```

The input validation checks:

- Valid vertex IDs
- Non-negative degree
- Correct number of neighbours
- No self-loops
- Exactly `V` adjacency lines
- Undirected edge consistency
- Correct number of edges

---

## PageRank

```text
V E
vertex degree neighbor1 neighbor2 ... neighbor_degree
...
DAMPING value
TOLERANCE value
MAX_ITERATIONS value
```

Example:

```text
5 4
0 1 1
1 1 2
2 1 3
3 1 4
4 0
DAMPING 0.85
TOLERANCE 0.000001
MAX_ITERATIONS 100
```

The input validation checks:

- Valid vertex IDs
- Correct neighbour counts
- Valid directed graph structure
- `0 < damping < 1`
- `tolerance > 0`
- `maxIterations > 0`

---

# Test Cases

The required test sizes are:

### Vertex Coloring

| Test             | Vertices |
| ---------------- | -------: |
| color_10.txt     |       10 |
| color_100.txt    |      100 |
| color_10000.txt  |   10,000 |
| color_50000.txt  |   50,000 |
| color_100000.txt |  100,000 |

### PageRank

| Test               | Vertices |
| ------------------ | -------: |
| pagerank_10.txt    |       10 |
| pagerank_100.txt   |      100 |
| pagerank_1000.txt  |    1,000 |
| pagerank_10000.txt |   10,000 |
| pagerank_50000.txt |   50,000 |

---

# Results

## Welsh–Powell Vertex Coloring

| Test File        | Vertices | Edges | Colors Used | Valid | Execution Time (ms) |
| ---------------- | -------: | ----: | ----------: | ----- | ------------------: |
| color_10.txt     |       10 |     14 |           3 | YES   |                   0.000000 |
| color_100.txt    |      100 |     250 |           4 | YES   |                  0.000000 |
| color_10000.txt  |   10,000 |     30000 |           6 | YES   |                   7.994000 |
| color_50000.txt  |   50,000 |     150000 |           6 | YES   |                   49.471000 |
| color_100000.txt |  100,000 |     300000 |           6 | YES   |                   140.077000 |

---

## PageRank

| Test File          | Vertices | Edges | Rank Sum | Iterations | Converged | Execution Time (ms) |
| ------------------ | -------: | ----: | -------: | ---------: | --------- | ------------------: |
| pagerank_10.txt    |       10 |     14 |        1.0000000000 |          29 | YES       |                   0.000000 |
| pagerank_100.txt   |      100 |     250 |        1.0000000000 |          22 | YES       |                   0.000000 |
| pagerank_1000.txt  |    1,000 |     3000 |        1.0000000000 |          22 | YES       |                   0.996000 |
| pagerank_10000.txt |   10,000 |     30000 |        1.0000000000 |          22 | YES       |                   13.131000 |
| pagerank_50000.txt |   50,000 |     150000 |        1.0000000000 |          22 | YES       |                   151.831000 |

---

# Compilation

From the repository root:

```powershell
g++ -std=c++17 common_wrapper/wrapper.cpp -o wrapper.exe
```

Run:

```powershell
.\wrapper.exe
```

Assignment 4 can then be compiled and tested through the wrapper menu.

Individual drivers can also be compiled directly:

```powershell
g++ -std=c++17 assignment_04/driver/vertex_coloring_driver.cpp assignment_04/src/vertex_coloring.cpp assignment_04/src/a4_graph_reader.cpp assignment_01/src/csr.cpp assignment_01/src/graph.cpp assignment_01/src/edge.cpp assignment_01/src/timer.cpp -o vertex_coloring_driver.exe
```

```powershell
g++ -std=c++17 assignment_04/driver/pagerank_driver.cpp assignment_04/src/pagerank.cpp assignment_04/src/a4_graph_reader.cpp assignment_01/src/csr.cpp assignment_01/src/graph.cpp assignment_01/src/edge.cpp assignment_01/src/timer.cpp -o pagerank_driver.exe
```
