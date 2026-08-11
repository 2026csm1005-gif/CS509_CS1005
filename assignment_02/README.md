# Assignment 02 - Shortest Path Algorithms

## 1. Assignment Overview

### Assignment Mode

**Individual Assignment**

### Objective

This assignment implements two shortest-path algorithms:

1. **Bellman-Ford**
2. **Floyd-Warshall**

Bellman-Ford computes single-source shortest paths in a directed weighted graph and supports negative edge weights while detecting negative-weight cycles.

Floyd-Warshall computes shortest paths between every pair of vertices using dynamic programming. It supports negative edge weights provided that the graph does not contain a negative-weight cycle.

The assignment also includes a cross-check between Bellman-Ford and Floyd-Warshall for graphs with 10 and 100 vertices.

---

# 2. Language and Environment

| Item                 | Details             |
| -------------------- | ------------------- |
| Programming Language | C++                 |
| Compiler             | MinGW g++           |
| Standard             | C++17               |
| Operating System     | Windows             |
| Compilation Standard | `-std=c++17`        |
| Timing Unit          | milliseconds (`ms`) |

The implementation uses C++17 features including `std::filesystem` in the common wrapper.

---

# 3. Algorithms Implemented

## 3.1 Bellman-Ford

Bellman-Ford solves the single-source shortest-path problem for a directed weighted graph.

It repeatedly relaxes all edges:

```text
if dist[u] + weight(u,v) < dist[v]
    dist[v] = dist[u] + weight(u,v)
```

The algorithm performs up to `V - 1` relaxation passes and then performs an additional pass to detect a reachable negative-weight cycle.

### Complexity

- Time: `O(V × E)`
- Space: `O(V)` for the shortest-distance information, excluding the graph representation.

The two largest Bellman-Ford graphs are kept sparse so that the `O(V × E)` execution remains practical.

### Required Vertex Sizes

| Test Size    | Vertices |
| ------------ | -------: |
| Small        |       10 |
| Small/Medium |      100 |
| Large        |   10,000 |
| Very Large   |   50,000 |
| Very Large   |  100,000 |

For the 50,000- and 100,000-vertex graphs, the number of edges is kept approximately within:

```text
E ≈ 2V to 4V
```

---

## 3.2 Floyd-Warshall

Floyd-Warshall computes the shortest distance between every pair of vertices.

For every intermediate vertex `k`, the algorithm updates every pair `(i,j)` using:

```text
dist[i][j] = min(dist[i][j],
                 dist[i][k] + dist[k][j])
```

The algorithm supports negative edge weights, provided that the graph does not contain a negative-weight cycle.

After the algorithm finishes, the diagonal is checked:

```text
dist[i][i] < 0
```

for any vertex indicates a negative-weight cycle.

### Complexity

- Time: `O(V³)`
- Space: `O(V²)`

Because of the cubic time and quadratic memory requirements, Floyd-Warshall is tested only on smaller graphs.

### Required Vertex Sizes

| Test Size    | Vertices |
| ------------ | -------: |
| Small        |       10 |
| Small/Medium |      100 |
| Medium       |      500 |
| Large        |    1,000 |
| Large        |    2,000 |

---

# 4. Graph Representation and Input Formats

## 4.1 Bellman-Ford Input

Bellman-Ford uses a directed graph represented through an adjacency-list input.

The graph uses vertex numbering from:

```text
0 to V-1
```

Negative edge weights are allowed because Bellman-Ford operates on directed graphs.

A negative-weight edge must not be treated as an undirected edge because traversing such an edge in both directions would itself create a negative-weight cycle.

The adjacency-list representation is converted to CSR using the CSR conversion functionality developed in Assignment 01.

The CSR conversion is preprocessing and is **not included** in the Bellman-Ford algorithm timing.

---

## 4.2 Floyd-Warshall Input

Floyd-Warshall uses a dense adjacency matrix.

The input format is:

```text
V
row 0 values
row 1 values
...
row (V-1) values
```

Each row contains exactly `V` space-separated entries.

An entry can be:

- An integer edge weight
- `INF` when there is no direct edge

The diagonal must contain `0`.

Example:

```text
5
0 3 8 INF -4
INF 0 INF 1 7
INF 4 0 INF INF
2 INF -5 0 INF
INF INF INF 6 0
```

Here:

```text
0 3 8 INF -4
```

is the first row of the direct-edge matrix.

The graph represented by the Floyd-Warshall matrix is **directed**. Therefore, `matrix[i][j]` and `matrix[j][i]` can represent different edges and different weights.

---

# 5. Output Format

## 5.1 Bellman-Ford

For a normal graph, the output contains:

```text
Vertices : <V>
Edges    : <E>
Source   : <source>

## Vertex    Distance

0         <distance>
1         <distance>
...

Negative cycle: none

# Bellman-Ford Execution Time : <time> ms
```

If a negative-weight cycle is detected, the output reports the negative-cycle condition.

For example:

```text
Negative cycle: true
```

The distance values are not treated as valid when a relevant negative cycle makes shortest paths undefined.

---

## 5.2 Floyd-Warshall

For a graph without a negative-weight cycle, the output contains the complete shortest-distance matrix:

```text
Distance matrix:

<shortest-distance matrix>

Negative cycle: false

Execution time: <time> ms
```

If a negative-weight cycle is detected:

```text
Negative cycle: true
```

is reported and the distance matrix is omitted.

For large matrices, output may be suppressed to avoid unnecessarily printing very large amounts of data. The algorithm execution itself is still performed and timed.

---

# 6. Runtime Measurement

Only the actual algorithm execution is included in the reported runtime.

The following operations are excluded from algorithm timing:

- File reading
- Input parsing
- Memory allocation performed during setup
- Adjacency-list construction
- Adjacency-list-to-CSR conversion
- Matrix construction
- Result printing
- File writing

For Bellman-Ford, the CSR structure is prepared before the timer starts.

For Floyd-Warshall, the input matrix is loaded before the timer starts.

The timer starts immediately before the algorithm call and stops immediately after the algorithm finishes.

All reported times use milliseconds (`ms`).

For very small inputs, the measured execution time may be displayed as:

```text
0.000000 ms
```

when the measured duration is below the displayed precision.

---

# 7. Cross-Check: Bellman-Ford vs Floyd-Warshall

For the graph sizes where both algorithms are required, Bellman-Ford is run once from every vertex.

This is done for:

```text
V = 10
V = 100
```

For each source vertex:

1. Bellman-Ford is executed using that vertex as the source.
2. The resulting distance vector is obtained.
3. The corresponding row of the Floyd-Warshall distance matrix is obtained.
4. The two results are compared element-by-element.

The expected result is:

```text
Mismatches : 0
Result     : PASS
```

The cross-check was implemented in:

```text
assignment_02/utilities/cross_check_bf_fw.cpp
```

The cross-check confirms that Bellman-Ford and Floyd-Warshall produce consistent shortest-path distances for the common graph sizes.

---

# 8. Test Cases

## 8.1 Bellman-Ford Test Files

The Bellman-Ford tests are stored in:

```text
assignment_02/tests/bellman_ford/
```

| Test File                           | Vertices | Purpose                                                             |
| ----------------------------------- | -------: | ------------------------------------------------------------------- |
| `bf_10.txt`                         |       10 | Manually controlled negative-weight graph with known shortest paths |
| `bf_100.txt`                        |      100 | Required medium-size graph                                          |
| `bf_10000.txt`                      |   10,000 | Required large graph                                                |
| `bf_50000.txt`                      |   50,000 | Required sparse large graph                                         |
| `bf_100000.txt`                     |  100,000 | Required sparse largest graph                                       |
| `bf_negative_cycle.txt`             |       10 | Negative-cycle detection                                            |
| `bf_unreachable_negative_cycle.txt` |       10 | Negative cycle not reachable from the selected source               |

The larger regular test cases are generated using:

```text
assignment_02/utilities/generate_bf_tests.cpp
```

The manually controlled `bf_10.txt` test is retained because it provides a small graph with known shortest-path results and negative edge weights.

---

## 8.2 Floyd-Warshall Test Files

The Floyd-Warshall tests are stored in:

```text
assignment_02/tests/floyd_warshall/
```

| Test File                 | Vertices | Purpose                               |
| ------------------------- | -------: | ------------------------------------- |
| `fw_example.txt`          |        5 | Assignment example input              |
| `fw_10.txt`               |       10 | Required small graph and cross-check  |
| `fw_100.txt`              |      100 | Required graph and cross-check        |
| `fw_500.txt`              |      500 | Required medium-size graph            |
| `fw_1000.txt`             |    1,000 | Required large graph                  |
| `fw_2000.txt`             |    2,000 | Required largest Floyd-Warshall graph |
| `fw_negative_weights.txt` |       10 | Negative edge-weight test             |
| `fw_negative_cycle.txt`   |       10 | Negative-cycle detection              |

The larger regular test cases are generated using:

```text
assignment_02/utilities/generate_fw_tests.cpp
```

---

# 9. Result Tables

The following tables cover all Assignment 2 test cases.

## 9.1 Bellman-Ford Results

| Mode   | Test File                           | Input Type                                    | Vertices |   Edges | Source | Negative Cycle | Expected Output             | Actual Output              | Algorithm Time | Status |
| ------ | ----------------------------------- | --------------------------------------------- | -------: | ------: | -----: | -------------- | --------------------------- | -------------------------- | -------------: | ------ |
| Single | `bf_10.txt`                         | Directed weighted adjacency list → CSR        |       10 |      15 |      0 | No             | Known shortest distances    | Correct distances obtained |    0.000000 ms | Pass   |
| Single | `bf_100.txt`                        | Directed weighted adjacency list → CSR        |      100 |       300 |      0 | No             | Correct shortest distances  | Correct result             |           0.000000 ms | Pass   |
| Single | `bf_10000.txt`                      | Directed weighted adjacency list → CSR        |   10,000 |       30,000 |      0 | No             | Correct shortest distances  | Correct result             |           3.999000 ms | Pass   |
| Single | `bf_50000.txt`                      | Sparse directed weighted adjacency list → CSR |   50,000 | 150,000 |      0 | No             | Correct shortest distances  | Correct result             |           23.067000 ms | Pass   |
| Single | `bf_100000.txt`                     | Sparse directed weighted adjacency list → CSR |  100,000 | 300,000 |      0 | No             | Correct shortest distances  | Correct result             |           51.956000 ms | Pass   |
| Single | `bf_negative_cycle.txt`             | Directed weighted adjacency list → CSR        |       4 |       4 |      0 | Yes            | Negative cycle detected     | Negative cycle detected    |           0.000000 ms | Pass   |
| Single | `bf_unreachable_negative_cycle.txt` | Directed weighted adjacency list → CSR        |       6 |       5 |      0 | Unreachable    | No reachable negative cycle | Correct result             |           0.000000 ms | Pass   |

---

## 9.2 Floyd-Warshall Results

| Mode   | Test File                 | Input Type                      | Vertices | Source | Negative Cycle | Expected Output                                  | Actual Output           | Algorithm Time | Status |
| ------ | ------------------------- | ------------------------------- | -------: | ------ | -------------- | ------------------------------------------------ | ----------------------- | -------------: | ------ |
| Single | `fw_example.txt`          | Dense directed adjacency matrix |        5 | N/A    | No             | Example shortest-distance matrix                 | Correct matrix          |           0.000000 ms | Pass   |
| Single | `fw_10.txt`               | Dense directed adjacency matrix |       10 | N/A    | No             | Shortest-distance matrix                         | Correct matrix          |    0.000000 ms | Pass   |
| Single | `fw_100.txt`              | Dense directed adjacency matrix |      100 | N/A    | No             | Shortest-distance matrix                         | Correct matrix          |           29.969000 ms | Pass   |
| Single | `fw_500.txt`              | Dense directed adjacency matrix |      500 | N/A    | No             | Shortest-distance matrix                         | Correct matrix          |           2775.672000 ms | Pass   |
| Single | `fw_1000.txt`             | Dense directed adjacency matrix |    1,000 | N/A    | No             | Shortest-distance matrix                         | Correct matrix          |           20812.964000 ms | Pass   |
| Single | `fw_2000.txt`             | Dense directed adjacency matrix |    2,000 | N/A    | No             | Shortest-distance matrix                         | Correct matrix          |           186143.252000 ms | Pass   |
| Single | `fw_negative_weights.txt` | Dense directed adjacency matrix |       10 | N/A    | No             | Correct shortest distances with negative weights | Correct result          |           0.000000 ms | Pass   |
| Single | `fw_negative_cycle.txt`   | Dense directed adjacency matrix |       10 | N/A    | Yes            | Negative cycle detected                          | Negative cycle detected |           0.000000 ms | Pass   |

---

# 10. Cross-Check Results

| Test File    | Vertices | Bellman-Ford Sources Checked | Mismatches | Result |
| ------------ | -------: | ---------------------------: | ---------: | ------ |
| `fw_10.txt`  |       10 |                           10 |          0 | PASS   |
| `fw_100.txt` |      100 |                          100 |          0 | PASS   |

For both common graph sizes, Bellman-Ford was executed from every vertex and the resulting distance vectors were compared against the corresponding Floyd-Warshall rows.

---

# 11. Source Files

```text
assignment_02/
│
├── README.md
│
├── driver/
│   ├── bf_driver.cpp
│   └── fw_driver.cpp
│
├── include/
│   ├── bellman_ford.h
│   ├── bf_graph_reader.h
│   ├── floyd_warshall.h
│   └── fw_matrix_reader.h
│
├── src/
│   ├── bellman_ford.cpp
│   ├── bf_graph_reader.cpp
│   ├── floyd_warshall.cpp
│   └── fw_matrix_reader.cpp
│
├── tests/
│   ├── bellman_ford/
│   │   ├── bf_10.txt
│   │   ├── bf_100.txt
│   │   ├── bf_10000.txt
│   │   ├── bf_50000.txt
│   │   ├── bf_100000.txt
│   │   ├── bf_negative_cycle.txt
│   │   └── bf_unreachable_negative_cycle.txt
│   │
│   └── floyd_warshall/
│       ├── fw_example.txt
│       ├── fw_10.txt
│       ├── fw_100.txt
│       ├── fw_500.txt
│       ├── fw_1000.txt
│       ├── fw_2000.txt
│       ├── fw_negative_weights.txt
│       └── fw_negative_cycle.txt
│
└── utilities/
    ├── cross_check_bf_fw.cpp
    ├── generate_bf_tests.cpp
    └── generate_fw_tests.cpp
```

---

# 12. Compilation

## 12.1 Bellman-Ford

From the repository root:

```powershell
g++ assignment_02/driver/bf_driver.cpp `
    assignment_02/src/bellman_ford.cpp `
    assignment_02/src/bf_graph_reader.cpp `
    assignment_01/src/csr.cpp `
    assignment_01/src/graph.cpp `
    assignment_01/src/edge.cpp `
    assignment_01/src/timer.cpp `
    -o bf_driver.exe
```

## 12.2 Floyd-Warshall

```powershell
g++ assignment_02/driver/fw_driver.cpp `
    assignment_02/src/floyd_warshall.cpp `
    assignment_02/src/fw_matrix_reader.cpp `
    assignment_01/src/timer.cpp `
    -o fw_driver.exe
```

---

# 13. Execution

## Bellman-Ford

Example:

```powershell
.\bf_driver.exe assignment_02/tests/bellman_ford/bf_10.txt
```

Another example:

```powershell
.\bf_driver.exe assignment_02/tests/bellman_ford/bf_100000.txt
```

## Floyd-Warshall

Example:

```powershell
.\fw_driver.exe assignment_02/tests/floyd_warshall/fw_10.txt
```

Another example:

```powershell
.\fw_driver.exe assignment_02/tests/floyd_warshall/fw_2000.txt
```

---

# 14. Test Generator Utilities

Random/larger test cases are generated using dedicated utility programs.

## Bellman-Ford Generator

Source:

```text
assignment_02/utilities/generate_bf_tests.cpp
```

The generator is used to create the required graph sizes, including large sparse graphs.

## Floyd-Warshall Generator

Source:

```text
assignment_02/utilities/generate_fw_tests.cpp
```

The generator creates dense adjacency-matrix inputs using the required `INF` representation.

The manually controlled test cases are retained separately where a known result or special edge condition is required.

---

# 15. Common Wrapper

Assignment 02 is integrated into the repository-level common wrapper.

The common wrapper is located at:

```text
common_wrapper/wrapper.cpp
```

It provides a single menu interface for the submitted assignments.

Current wrapper functionality includes:

```text
1. Display available algorithms
2. Compile an assignment
3. Run one selected test file
4. Run all test files for an assignment
5. Compile all assignments
6. Run all submitted algorithms
7. Exit
```

The wrapper invokes the dedicated drivers rather than replacing them.

### Compile the wrapper

```powershell
g++ -std=c++17 common_wrapper/wrapper.cpp -o wrapper.exe
```

### Run the wrapper

```powershell
.\wrapper.exe
```

Assignment 02 algorithms available through the wrapper are:

```text
Bellman-Ford
Floyd-Warshall
```

The wrapper also reports clear errors when required source files, test files or executables are unavailable.

---

# 16. Complexity Summary

| Algorithm      | Time Complexity | Space Complexity                  |
| -------------- | --------------- | --------------------------------- |
| Bellman-Ford   | `O(V × E)`      | `O(V)` algorithm distance storage |
| Floyd-Warshall | `O(V³)`         | `O(V²)`                           |

Bellman-Ford is therefore suitable for the larger sparse graphs, while Floyd-Warshall is restricted to smaller graph sizes because of its cubic time and quadratic memory requirements.

---

# 17. Important Implementation Notes

1. Bellman-Ford graphs are directed.
2. Negative edge weights are supported by both algorithms.
3. Negative-weight cycles are explicitly tested.
4. Floyd-Warshall uses `INF` to represent the absence of a direct edge.
5. Floyd-Warshall uses `0` on the diagonal of the input matrix.
6. CSR conversion from Assignment 01 is reused by Bellman-Ford.
7. CSR conversion time is excluded from Bellman-Ford timing.
8. Input loading and output printing are excluded from algorithm timing.
9. Floyd-Warshall does not use CSR.
10. The two largest Bellman-Ford graphs are kept sparse.
11. Full Floyd-Warshall matrices are printed only for manageable graph sizes; large output may be suppressed.
12. Negative-cycle detection is performed after the main shortest-path computation.
13. For the common graph sizes of 10 and 100 vertices, Bellman-Ford and Floyd-Warshall results are cross-checked.

---

# 18. Final Test Status

All implemented Assignment 02 algorithms and their test cases were executed successfully during development.

### Bellman-Ford

```text
bf_10.txt                       PASS
bf_100.txt                      PASS
bf_10000.txt                    PASS
bf_50000.txt                    PASS
bf_100000.txt                   PASS
bf_negative_cycle.txt           PASS
bf_unreachable_negative_cycle   PASS
```

### Floyd-Warshall

```text
fw_example.txt                  PASS
fw_10.txt                       PASS
fw_100.txt                      PASS
fw_500.txt                      PASS
fw_1000.txt                     PASS
fw_2000.txt                     PASS
fw_negative_weights.txt        PASS
fw_negative_cycle.txt          PASS
```

### Cross-Check

```text
fw_10.txt   → 10 sources checked → 0 mismatches → PASS
fw_100.txt  → 100 sources checked → 0 mismatches → PASS
```

---

# 19. References

- https://cp-algorithms.com
- https://networkx.org
- https://www.tandfonline.com
- https://cppreference.com