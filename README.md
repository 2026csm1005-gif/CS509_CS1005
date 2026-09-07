# CS509 – PG Software Lab

## Student Details

Name: Aman Singh Bisht

Entry Number: 2026CSM1005

## Programming Language

C++

```text
This repository contains the implementations for **CS509 (PG Software Lab) Assignments 01–04**. The assignments cover matrix computation, sparse graph representation, shortest-path algorithms, minimum spanning trees, graph coloring, and PageRank.
```
---

## Environment

| Component        | Details              |
| ---------------- | -------------------- |
| Language         | C++                  |
| Standard         | C++17                |
| Compiler         | MinGW g++            |
| Operating System | Windows 11           |
| Version Control  | Git & GitHub Desktop |
| Timing Unit      | milliseconds (`ms`)  |

---

## Repository Structure

```text
CS509_CS1005/
│
├── README.md
├── common_wrapper/
│   └── wrapper.cpp
│
├── assignment_01/
│   ├── include/
│   ├── src/
│   ├── driver/
│   ├── tests/
│   ├── outputs/
│   └── README.md
│
├── assignment_02/
│   ├── include/
│   ├── src/
│   ├── driver/
│   ├── tests/
│   ├── utilities/
│   └── README.md
│
├── assignment_03/
│   ├── include/
│   ├── src/
│   ├── driver/
│   ├── tests/
│   ├── utilities/
│   └── README.md
│
├── assignment_04/
│   ├── include/
│   ├── src/
│   ├── driver/
│   ├── tests/
│   ├── utilities/
│   └── README.md
│
└── .gitignore
```

---

# Assignment 01 – GEMM and CSR

Assignment 01 implements **General Matrix Multiplication (GEMM)** and **Compressed Sparse Row (CSR)** graph representation.

## Algorithms

### Simple GEMM

Classical matrix multiplication using three nested loops.

- Time: `O(M × K × N)`
- Space: `O(M × N)`

### Blocking GEMM

Divides matrices into smaller blocks to improve cache locality.

- Time: `O(M × K × N)`
- Space: `O(M × N)`

Although both algorithms have the same asymptotic complexity, Blocking GEMM provides better practical performance for larger matrices.

### CSR Conversion

The graph is converted through:

```text
Adjacency List → Edge List → CSR
```

CSR consists of:

- `row_ptr`
- `col_idx`
- `values`

Complexity:

| Operation                  |       Time |      Space |
| -------------------------- | ---------: | ---------: |
| Adjacency List → Edge List |     `O(E)` |     `O(E)` |
| Edge List → CSR            | `O(V + E)` | `O(V + E)` |

The CSR implementation is reused by later graph assignments.

## Results

### GEMM

| Test               | Dimensions        |   Simple GEMM | Blocking GEMM | Status |
| ------------------ | ----------------- | ------------: | ------------: | ------ |
| `gemm_test_01.txt` | 2×3 × 3×2         |   0.000000 ms |   0.000000 ms | Pass   |
| `gemm_test_02.txt` | 3×3 × 3×3         |   0.000000 ms |   0.000000 ms | Pass   |
| `gemm_test_03.txt` | 3×3 × 3×3         |   0.000000 ms |   0.000000 ms | Pass   |
| `gemm_test_04.txt` | 3×3 × 3×3         |   0.000000 ms |   0.000000 ms | Pass   |
| `gemm_test_05.txt` | 4×2 × 2×5         |   0.000000 ms |   0.000000 ms | Pass   |
| `gemm_test_06.txt` | 3×3 × 3×3         |   0.000000 ms |   0.000000 ms | Pass   |
| `gemm_test_07.txt` | 10×10 × 10×10     |   0.000000 ms |   0.000000 ms | Pass   |
| `gemm_test_08.txt` | 100×100 × 100×100 |   8.999000 ms |   7.480000 ms | Pass   |
| `gemm_test_09.txt` | 250×250 × 250×250 |  93.945000 ms |  68.441000 ms | Pass   |
| `gemm_test_10.txt` | 500×500 × 500×500 | 840.617000 ms | 600.030000 ms | Pass   |

### CSR

| Test               | Vertices |  Edges | Conversion Time | Status |
| ------------------ | -------: | -----: | --------------: | ------ |
| `csr_test_01.txt`  |        5 |      5 |     0.000000 ms | Pass   |
| `csr_test_02.txt`  |        1 |      0 |     0.000000 ms | Pass   |
| `csr_test_03.txt`  |        2 |      1 |     0.000000 ms | Pass   |
| `csr_test_04.txt`  |        5 |      2 |     0.000000 ms | Pass   |
| `csr_test_05.txt`  |        6 |      3 |     0.000000 ms | Pass   |
| `csr_test_06.txt`  |        5 |      4 |     0.000000 ms | Pass   |
| `csr_test_07.txt`  |        5 |      5 |     0.000000 ms | Pass   |
| `csr_test_08.txt`  |        4 |      6 |     0.000000 ms | Pass   |
| `csr_test_09.txt`  |    1,000 | 10,000 |     0.998000 ms | Pass   |
| `csr_test_010.txt` |    2,500 |  7,500 |     1.357000 ms | Pass   |

---

# Assignment 02 – Shortest Path Algorithms

Assignment 02 implements **Bellman-Ford** and **Floyd-Warshall** shortest-path algorithms.

## Algorithms

### Bellman-Ford

Computes single-source shortest paths in a directed weighted graph and supports negative edge weights and negative-cycle detection.

- Time: `O(V × E)`
- Space: `O(V)`

Required sizes:

```text
10, 100, 10,000, 50,000, 100,000 vertices
```

The largest graphs are kept sparse.

### Floyd-Warshall

Computes shortest paths between every pair of vertices.

- Time: `O(V³)`
- Space: `O(V²)`

Required sizes:

```text
10, 100, 500, 1,000, 2,000 vertices
```

Negative-weight cycle detection is performed using the diagonal of the final distance matrix.

## Results

### Bellman-Ford

| Test                                |       V |       E | Negative Cycle |         Time | Status |
| ----------------------------------- | ------: | ------: | -------------- | -----------: | ------ |
| `bf_10.txt`                         |      10 |      15 | No             |  0.000000 ms | Pass   |
| `bf_100.txt`                        |     100 |     300 | No             |  0.000000 ms | Pass   |
| `bf_10000.txt`                      |  10,000 |  30,000 | No             |  3.999000 ms | Pass   |
| `bf_50000.txt`                      |  50,000 | 150,000 | No             | 23.067000 ms | Pass   |
| `bf_100000.txt`                     | 100,000 | 300,000 | No             | 51.956000 ms | Pass   |
| `bf_negative_cycle.txt`             |       4 |       4 | Yes            |  0.000000 ms | Pass   |
| `bf_unreachable_negative_cycle.txt` |       6 |       5 | Unreachable    |  0.000000 ms | Pass   |

### Floyd-Warshall

| Test                      |     V | Negative Cycle |             Time | Status |
| ------------------------- | ----: | -------------- | ---------------: | ------ |
| `fw_example.txt`          |     5 | No             |      0.000000 ms | Pass   |
| `fw_10.txt`               |    10 | No             |      0.000000 ms | Pass   |
| `fw_100.txt`              |   100 | No             |     29.969000 ms | Pass   |
| `fw_500.txt`              |   500 | No             |   2775.672000 ms | Pass   |
| `fw_1000.txt`             | 1,000 | No             |  20812.964000 ms | Pass   |
| `fw_2000.txt`             | 2,000 | No             | 186143.252000 ms | Pass   |
| `fw_negative_weights.txt` |    10 | No             |      0.000000 ms | Pass   |
| `fw_negative_cycle.txt`   |    10 | Yes            |      0.000000 ms | Pass   |

### Bellman-Ford / Floyd-Warshall Cross-Check

| Test         | Vertices | Sources Checked | Mismatches | Result |
| ------------ | -------: | --------------: | ---------: | ------ |
| `fw_10.txt`  |       10 |              10 |          0 | PASS   |
| `fw_100.txt` |      100 |             100 |          0 | PASS   |

Bellman-Ford reuses the CSR implementation from Assignment 01. CSR conversion is performed before timing and is excluded from the algorithm execution time.

---

# Assignment 03 – Minimum Spanning Tree

Assignment 03 implements **Kruskal's Algorithm** and **Prim's Algorithm** for weighted undirected graphs. Both algorithms use the same input graphs and reuse the CSR implementation from Assignment 01.

## Algorithms

### Kruskal's Algorithm

- Builds an edge list.
- Sorts edges by weight.
- Uses Disjoint Set Union (Union-Find).
- Uses path compression and union by rank.
- Selects edges without creating cycles.

### Prim's Algorithm

- Starts from vertex `0`.
- Uses a min-priority queue.
- Repeatedly selects the minimum-weight outgoing edge.

## Complexity

| Algorithm | Time Complexity | Space Complexity |
| --------- | --------------- | ---------------- |
| Kruskal   | `O(E log E)`    | `O(V + E)`       |
| Prim      | `O(E log V)`    | `O(V + E)`       |

## Test Graphs

All generated graphs are connected, weighted, undirected, and sparse.

| Test             | Vertices |   Edges |
| ---------------- | -------: | ------: |
| `mst_10.txt`     |       10 |      20 |
| `mst_100.txt`    |      100 |     300 |
| `mst_10000.txt`  |   10,000 |  30,000 |
| `mst_50000.txt`  |   50,000 | 150,000 |
| `mst_100000.txt` |  100,000 | 300,000 |

## Results

| Test             |       V |       E | Kruskal Weight | Prim Weight |  Kruskal Time |     Prim Time | Equal? | Status |
| ---------------- | ------: | ------: | -------------: | ----------: | ------------: | ------------: | :----: | :----: |
| `mst_10.txt`     |      10 |      20 |            119 |         119 |   0.000000 ms |   0.000000 ms |  Yes   |  Pass  |
| `mst_100.txt`    |     100 |     300 |          1,996 |       1,996 |   0.000000 ms |   0.991000 ms |  Yes   |  Pass  |
| `mst_10000.txt`  |  10,000 |  30,000 |        202,789 |     202,789 |  13.245000 ms | 132.410000 ms |  Yes   |  Pass  |
| `mst_50000.txt`  |  50,000 | 150,000 |      1,013,724 |   1,013,724 |  70.049000 ms | 300.876000 ms |  Yes   |  Pass  |
| `mst_100000.txt` | 100,000 | 300,000 |      2,021,442 |   2,021,442 | 147.927000 ms | 688.085000 ms |  Yes   |  Pass  |

Both algorithms produced the same MST weight for every test case.

---

# Assignment 04 – Vertex Coloring and PageRank

Assignment 04 implements **Greedy Vertex Coloring using Welsh–Powell** and **PageRank**.

## Algorithms

### Welsh–Powell Vertex Coloring

1. Calculate the degree of every vertex.
2. Sort vertices in non-increasing order of degree.
3. Assign the smallest available color.
4. Continue greedily until all vertices are colored.
5. Validate the resulting coloring.

Complexity:

- Time: `O(V log V + E)`
- Space: `O(V + E)`

The implementation uses CSR for efficient adjacency access.

### PageRank

PageRank is computed using:

```text
PR(v) = (1-d)/N + d × Σ(PR(u) / outdegree(u))
```

The implementation:

- Initializes every rank to `1/N`.
- Uses damping factor `0.85`.
- Handles dangling vertices.
- Performs simultaneous updates.
- Stops when the rank change reaches the tolerance or maximum iterations.

Complexity:

- Time: `O(I(V + E))`
- Space: `O(V + E)`

## Test Sizes

### Vertex Coloring

```text
10, 100, 10,000, 50,000, 100,000 vertices
```

### PageRank

```text
10, 100, 1,000, 10,000, 50,000 vertices
```

## Results

### Welsh–Powell Vertex Coloring

| Test               | Vertices |   Edges | Colors Used | Valid |          Time |
| ------------------ | -------: | ------: | ----------: | :---: | ------------: |
| `color_10.txt`     |       10 |      14 |           3 |  YES  |   0.000000 ms |
| `color_100.txt`    |      100 |     250 |           4 |  YES  |   0.000000 ms |
| `color_10000.txt`  |   10,000 |  30,000 |           6 |  YES  |   7.994000 ms |
| `color_50000.txt`  |   50,000 | 150,000 |           6 |  YES  |  49.471000 ms |
| `color_100000.txt` |  100,000 | 300,000 |           6 |  YES  | 140.077000 ms |

### PageRank

| Test                 | Vertices |   Edges |     Rank Sum | Iterations | Converged |          Time |
| -------------------- | -------: | ------: | -----------: | ---------: | :-------: | ------------: |
| `pagerank_10.txt`    |       10 |      14 | 1.0000000000 |         29 |    YES    |   0.000000 ms |
| `pagerank_100.txt`   |      100 |     250 | 1.0000000000 |         22 |    YES    |   0.000000 ms |
| `pagerank_1000.txt`  |    1,000 |   3,000 | 1.0000000000 |         22 |    YES    |   0.996000 ms |
| `pagerank_10000.txt` |   10,000 |  30,000 | 1.0000000000 |         22 |    YES    |  13.131000 ms |
| `pagerank_50000.txt` |   50,000 | 150,000 | 1.0000000000 |         22 |    YES    | 151.831000 ms |

All PageRank test cases converged with rank sum approximately equal to `1.0`.

---

# Common Wrapper

The repository contains a **common wrapper** at:

```text
common_wrapper/wrapper.cpp
```

The wrapper provides a single interface for compiling and running the algorithms from all four assignments.

Current algorithms available through the wrapper:

```text
Assignment 01
  1. GEMM
  2. CSR

Assignment 02
  3. Bellman-Ford
  4. Floyd-Warshall

Assignment 03
  5. Kruskal MST
  6. Prim MST

Assignment 04
  7. Welsh-Powell Vertex Coloring
  8. PageRank
```

The wrapper supports:

- Displaying available algorithms.
- Compiling individual assignments.
- Compiling all assignments.
- Running one selected test case.
- Running all tests for an assignment.
- Running all submitted algorithms.
- Reporting missing files or executables.

## Compile and Run Wrapper

From the repository root:

```powershell
g++ -std=c++17 common_wrapper/wrapper.cpp -o wrapper.exe
```

Run:

```powershell
.\wrapper.exe
```

---

# Runtime Measurement

For all assignments, timing is intended to measure the **algorithm execution only**.

The following operations are excluded wherever applicable:

- Input file reading
- Input parsing
- Graph/matrix construction
- Memory/setup operations
- CSR conversion when used as preprocessing
- Result formatting
- Printing

The timer starts immediately before the algorithm call and stops immediately after the algorithm completes.

For very small inputs, execution times may appear as:

```text
0.000000 ms
```

because the measured duration is below the displayed precision.

---

# Complexity Summary

| Assignment | Algorithm       | Time Complexity  | Space Complexity |
| ---------- | --------------- | ---------------- | ---------------- |
| 01         | Simple GEMM     | `O(M × K × N)`   | `O(M × N)`       |
| 01         | Blocking GEMM   | `O(M × K × N)`   | `O(M × N)`       |
| 01         | Edge List → CSR | `O(V + E)`       | `O(V + E)`       |
| 02         | Bellman-Ford    | `O(V × E)`       | `O(V)`           |
| 02         | Floyd-Warshall  | `O(V³)`          | `O(V²)`          |
| 03         | Kruskal         | `O(E log E)`     | `O(V + E)`       |
| 03         | Prim            | `O(E log V)`     | `O(V + E)`       |
| 04         | Welsh–Powell    | `O(V log V + E)` | `O(V + E)`       |
| 04         | PageRank        | `O(I(V + E))`    | `O(V + E)`       |

---

# Overall Result

All four assignments were implemented and tested successfully.

- **Assignment 01:** Simple GEMM, Blocking GEMM, and CSR conversion passed all listed tests.
- **Assignment 02:** Bellman-Ford and Floyd-Warshall passed all tests, including negative-cycle cases. The cross-check for 10- and 100-vertex graphs produced **0 mismatches**.
- **Assignment 03:** Kruskal and Prim produced identical MST weights for all required graph sizes.
- **Assignment 04:** Welsh–Powell produced valid colorings, and PageRank converged for all required test cases with rank sum approximately `1.0`.
- **Common Wrapper:** Provides a unified interface for compiling and testing all four assignments.

The repository also demonstrates reuse of common components, particularly the **CSR graph representation and Timer from Assignment 01**, across subsequent graph assignments.
