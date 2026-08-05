# Assignment 01 – General Matrix Multiplication (GEMM) and CSR Graph

## Repository Overview

This repository contains the implementation of **Assignment 01** for the **CS509 Programming Laboratory** course. The assignment has been developed following modular software engineering practices by separating the implementation into header files, source files, dedicated driver programs, test cases, and documentation.

The objectives of this assignment are:

- Implement **General Matrix Multiplication (GEMM)** using:

  - Simple GEMM
  - Blocking GEMM

- Implement **Compressed Sparse Row (CSR)** graph representation from an adjacency-list input.
- Measure only the algorithm execution time as specified in the assignment guidelines.
- Maintain a clean, modular, and maintainable project structure suitable for future assignments.

---

# Student Details

| Item                | Details                                                       |
| ------------------- | ------------------------------------------------------------- |
| **Course**          | CS509 – Programming Laboratory                                |
| **Assignment**      | Assignment 01                                                 |
| **Assignment Mode** | Individual                                                    |
| **Student Name**    | Aman Singh Bisht                                              |
| **Entry Number**    | 2026CSM1005                                                   |

---

# Language and Environment

| Component                | Details              |
| ------------------------ | -------------------- |
| **Programming Language** | C++                  |
| **Compiler**             | g++ (MinGW GCC)      |
| **C++ Standard**         | C++17                |
| **Operating System**     | Windows 11           |
| **IDE / Editor**         | Visual Studio Code   |
| **Version Control**      | Git & GitHub Desktop |

---

# Directory Structure

```text
CS509_CS1005/
│
├── README.md
│
├── common_wrapper/
│   └── wrapper.cpp
│
├── assignment_01/
│   │
│   ├── include/
│   │   ├── matrix.h
│   │   ├── gemm.h
│   │   ├── graph.h
│   │   ├── edge.h
│   │   ├── csr.h
│   │   └── timer.h
│   │
│   ├── src/
│   │   ├── matrix.cpp
│   │   ├── gemm.cpp
│   │   ├── graph.cpp
│   │   ├── edge.cpp
│   │   ├── csr.cpp
│   │   └── timer.cpp
│   │
│   ├── driver/
│   │   ├── driver.cpp
│   │   └── csr_driver.cpp
│   │
│   ├── tests/
│   │   ├── gemm/
│   │   └── csr/
│   │
│   ├── outputs/
│   │
│   └── README.md
│
└── .gitignore
```

---

# Common Wrapper

The repository contains a **common wrapper** that serves as a single interface for executing the implemented assignments.

### Features

- Display available assignments/algorithms.
- Compile the GEMM driver.
- Compile the CSR driver.
- Compile all available assignments.
- Execute a selected GEMM test case.
- Execute all GEMM test cases.
- Execute a selected CSR test case.
- Execute all CSR test cases.
- Display appropriate error messages whenever an executable or test file is unavailable.

The wrapper invokes the dedicated driver program for each assignment and does **not** replace the individual driver implementations.

Note: Wrapper should be executed from Root Directory, ex: common_wrapper\wrapper.exe from Root Directory.

---

# Assignment 01 – General Matrix Multiplication (GEMM)

## Assignment Mode

**Individual**

---

## Objective

General Matrix Multiplication (GEMM) computes the product of two matrices.

For matrices:

- **A** of size **M × K**
- **B** of size **K × N**

the output matrix **C** has dimensions **M × N**, where each element is computed as:

C[i][j] = Σ(k = 0 to K - 1) A[i][k] × B[k][j]

Two implementations have been developed:

- **Simple GEMM** using the conventional triple nested-loop algorithm.
- **Blocking GEMM**, which divides matrices into smaller blocks to improve cache locality and reduce cache misses.

Both implementations produce identical output matrices for the same input.

---

# Algorithm / Approach

## Simple GEMM

The Simple GEMM implementation follows the classical matrix multiplication algorithm.

For every element of the output matrix:

1. Select one row from matrix **A**.
2. Select one column from matrix **B**.
3. Multiply corresponding elements.
4. Sum all products.
5. Store the result in the corresponding position of matrix **C**.

The implementation uses three nested loops and directly computes each element of the resultant matrix.

---

## Blocking GEMM

Blocking GEMM (also called **Tiled GEMM**) improves memory performance by dividing the matrices into smaller square blocks.

Instead of processing the complete matrices row-by-row, the algorithm:

1. Divides matrices into fixed-size blocks.
2. Multiplies one block of matrix **A** with one block of matrix **B**.
3. Accumulates the partial results into the corresponding block of matrix **C**.
4. Repeats the process until all blocks have been processed.

This technique significantly improves cache utilization for large matrices while maintaining the same mathematical result as the Simple GEMM implementation.

---

# Input Format

The input file follows the format:

```text
RowsA ColumnsA ColumnsB

Matrix A

Matrix B
```

### Example Input

```text
2 3 2

1 2 3
4 5 6

7 8
9 10
11 12
```

This represents:

Matrix **A**

```text
1 2 3
4 5 6
```

Matrix **B**

```text
7  8
9 10
11 12
```

---

# Output

The program prints:

- Matrix A
- Matrix B
- Result matrix using **Simple GEMM**
- Result matrix using **Blocking GEMM**
- Execution time of Simple GEMM
- Execution time of Blocking GEMM

Both algorithms are expected to produce identical result matrices.

---

# File Structure

```text
assignment_01/

include/
│
├── matrix.h
├── gemm.h
└── timer.h

src/
│
├── matrix.cpp
├── gemm.cpp
└── timer.cpp

driver/
│
└── driver.cpp

tests/
│
└── gemm/

outputs/

README.md
```

---

# Compilation

Compile the GEMM driver using:

```bash
g++ driver/driver.cpp src/matrix.cpp src/gemm.cpp src/timer.cpp -o gemm_driver
```

---

# Execution

Run a specific test case:

```bash
gemm_driver.exe tests/gemm/gemm_test_01.txt
```

or on Linux:

```bash
./gemm_driver tests/gemm/gemm_test_01.txt
```
---

# Assignment 01 – Compressed Sparse Row (CSR) Graph

## Assignment Mode

**Individual**

---

# Objective

The objective of this part of the assignment is to convert a graph represented as an **Adjacency List** into the **Compressed Sparse Row (CSR)** representation.

CSR is a compact storage format widely used for sparse graphs and sparse matrices because it stores only the non-zero (or existing) edges, thereby reducing memory usage.

The generated CSR representation will serve as the input format for future graph algorithms such as **Breadth First Search (BFS)**, **Depth First Search (DFS)** and **Single Source Shortest Path (SSSP)**.

---

# Algorithm / Approach

The implementation is divided into multiple stages.

### Step 1 – Read Graph

The graph is read from the input file in **Adjacency List** format.

Each vertex stores its neighbouring vertices.

---

### Step 2 – Convert Adjacency List to Edge List

The adjacency list is traversed to generate an edge list.

Each edge is represented as

```text id="2pkmhr"
(Source Vertex, Destination Vertex, Weight)
```

For the current implementation, all edge weights are assumed to be **1**.

---

### Step 3 – Convert Edge List to CSR

The edge list is converted into the three CSR arrays.

### row_ptr

Stores the starting index of every vertex's neighbour list.

### col_idx

Stores the destination vertices.

### values

Stores the edge weights.

---

# Input Format

The graph input follows the adjacency-list representation.

```text id="r8elxm"
Number_of_Vertices Number_of_Edges

Vertex Degree Neighbour1 Neighbour2 ...

Vertex Degree Neighbour1 ...

...
```

---

## Example Input

```text id="3v3vve"
5 5

0 2 1 2
1 2 0 3
2 3 0 3 4
3 2 1 2
4 1 2
```

This graph contains

- Vertices = 5
- Edges = 5

---

# Output

The program prints

- Original Adjacency List
- Edge List Representation
- CSR Representation

  - row_ptr
  - col_idx
  - values

- CSR Conversion Time

---

# Helper Functions

The following helper functions are used.

| Function         | Purpose                              |
| ---------------- | ------------------------------------ |
| Read Graph       | Reads graph from the input file      |
| Print Graph      | Displays adjacency list              |
| Create Edge List | Converts adjacency list to edge list |
| Print Edge List  | Displays generated edge list         |
| Convert to CSR   | Generates CSR arrays                 |
| Print CSR        | Displays row_ptr, col_idx and values |
| Timer            | Measures CSR conversion time         |

---

# File Structure

```text id="w3f0af"
assignment_01/

include/
│
├── graph.h
├── edge.h
├── csr.h
└── timer.h

src/
│
├── graph.cpp
├── edge.cpp
├── csr.cpp
└── timer.cpp

driver/
│
└── csr_driver.cpp

tests/
│
└── csr/

outputs/

README.md
```

---

# Compilation

Compile the CSR driver using

```bash id="lmkny8"
g++ driver/csr_driver.cpp src/graph.cpp src/edge.cpp src/csr.cpp src/timer.cpp -o csr_driver
```

---

# Execution

Run a single test case

```bash id="ejg2ie"
csr_driver.exe tests/csr/csr_test_01.txt
```

or on Linux

```bash id="0mg0uv"
./csr_driver tests/csr/csr_test_01.txt
```

---

# Test Cases and Result Table

## General Matrix Multiplication (GEMM)

### Simple GEMM and Blocking GEMM

| Mode   | Test File        | Input Type         | Input Size / Dimensions | Expected Output                   | Actual Output | Algorithm Time                   |
| ------ | ---------------- | ------------------ | ----------------------- | --------------------------------- | ------------- | -------------------------------- |
| Single | gemm_test_01.txt | Integer Matrix     | A: 2×3, B: 3×2          | Matrix product computed correctly | Matched       | Simple: **0.000000 ms, Blocking: 0.000000** ms |
| Single | gemm_test_02.txt | Integer Matrix     | A: 3×3, B: 3×3          | Matrix product computed correctly | Matched       | Simple: **0.000000 ms, Blocking: 0.000000** ms |
| Single | gemm_test_03.txt | Zero Matrix   | A: 3×3, B: 3×3          | Matrix product computed correctly     | Matched       | Simple: **0.000000 ms, Blocking: 0.000000** ms |
| Single | gemm_test_04.txt | Single Element Matrix        | A: 3×3, B: 3×3          | Matrix product computed correctly                       | Matched       | Simple: **0.000000 ms, Blocking: 0.000000** ms |
| Single | gemm_test_05.txt | Rectangular Matrix | A: 4×2, B: 2×5          | Matrix product computed correctly | Matched       | Simple: **0.000000 ms, Blocking: 0.000000** ms |
| Single | gemm_test_06.txt | Negative Values    | A: 3×3, B: 3×3          | Matrix product computed correctly | Matched       | Simple: **0.000000 ms, Blocking: 0.000000** ms |
| Single | gemm_test_07.txt | Mixed Values       | A: 10×10, B: 10×10          | Matrix product computed correctly | Matched       | Simple: **0.000000 ms, Blocking: 0.000000** ms |
| Single | gemm_test_08.txt | Random Matrix      | A: 100×100, B: 100×100      | Matrix product computed correctly | Matched       | Simple: **8.999000 ms, Blocking: 7.480000** ms |
| Single | gemm_test_09.txt | Random Matrix      | A: 250×250, B: 250×250  | Matrix product computed correctly | Matched       | Simple: **93.945000 ms, Blocking: 68.441000** ms |
| Single | gemm_test_10.txt | Random Matrix      | A: 500×500, B: 500×500  | Matrix product computed correctly | Matched       | Simple: **840.617000 ms, Blocking: 600.030000** ms |





# CSR Result Table

| Mode   | Test File       | Input Type           | Input Size         | Expected Output    | Actual Output | Algorithm Time |
| ------ | --------------- | -------------------- | ------------------ | ------------------ | ------------- | -------------- |
| Single | csr_test_01.txt | Adjacency List → CSR | V = 5, E = 5       | Correct CSR arrays | Matched       | 0.000000 ms      |
| Single | csr_test_02.txt | Adjacency List → CSR | V = 1, E = 0       | Correct CSR arrays | Matched       | 0.000000 ms      |
| Single | csr_test_03.txt | Adjacency List → CSR | V = 2, E = 1       | Correct CSR arrays | Matched       | 0.000000 ms      |
| Single | csr_test_04.txt | Adjacency List → CSR | V = 5, E = 2       | Correct CSR arrays | Matched       | 0.000000 ms      |
| Single | csr_test_05.txt | Adjacency List → CSR | V = 6, E = 3      | Correct CSR arrays | Matched       | 0.000000 ms      |
| Single | csr_test_06.txt | Adjacency List → CSR | V = 5, E = 4     | Correct CSR arrays | Matched       | 0.000000 ms      |
| Single | csr_test_07.txt | Adjacency List → CSR | V = 5, E = 5     | Correct CSR arrays | Matched       | 0.000000 ms      |
| Single | csr_test_08.txt | Adjacency List → CSR | V = 4, E = 6     | Correct CSR arrays | Matched       | 0.000000 ms      |
| Single | csr_test_09.txt | Adjacency List → CSR | V = 1000, E = 10000   | Correct CSR arrays | Matched       | 0.998000 ms      |
| Single | csr_test_010.txt | Adjacency List → CSR | V = 2500, E = 7500 | Correct CSR arrays | Matched       | 1.357000 ms      |

---

# Complexity Analysis

## Adjacency List → Edge List

**Time Complexity**

```text id="f0kjha"
O(E)
```

**Space Complexity**

```text id="uxezlu"
O(E)
```

---

## Edge List → CSR

**Time Complexity**

```text id="b4vop8"
O(V + E)
```

**Space Complexity**

```text id="0ynzpd"
O(V + E)
```

where

- **V** = Number of vertices
- **E** = Number of edges

---

# Runtime Measurement

The execution time reported in this assignment follows the CS509 laboratory guidelines.

### GEMM

The timer starts immediately before the selected GEMM algorithm is executed and stops immediately after the algorithm completes.

The following operations are **not included** in the measured execution time:

- Reading input files
- Matrix allocation
- Matrix initialization
- Output formatting
- Printing the result matrix

Only the execution time of the **Simple GEMM** and **Blocking GEMM** algorithms is reported.

---

### CSR

The timer starts immediately before the **Edge List → CSR conversion** and stops immediately after the CSR representation has been generated.

The following preprocessing operations are **excluded** from the measured execution time:

- Reading the graph from the input file
- Constructing the adjacency list
- Creating the edge list
- Output formatting
- Printing the CSR arrays

Only the CSR conversion algorithm is timed, ensuring that the reported execution time represents the algorithm alone, in accordance with the assignment requirements.

# Complexity Analysis

## General Matrix Multiplication (GEMM)

### Simple GEMM

| Property             | Complexity   |
| -------------------- | ------------ |
| **Time Complexity**  | O(M × K × N) |
| **Space Complexity** | O(M × N)     |

The Simple GEMM implementation uses three nested loops to compute each element of the resultant matrix. Every element of matrix **A** is multiplied with the corresponding element of matrix **B**, resulting in a time complexity of **O(M × K × N)**.

---

### Blocking GEMM

| Property             | Complexity   |
| -------------------- | ------------ |
| **Time Complexity**  | O(M × K × N) |
| **Space Complexity** | O(M × N)     |

Although Blocking GEMM has the same asymptotic time complexity as the Simple GEMM algorithm, it improves cache locality by processing the matrices in smaller blocks. This reduces cache misses and generally provides better practical performance for larger matrices.

---

## CSR Graph Conversion

The CSR conversion is performed in two stages.

### Stage 1: Adjacency List → Edge List

| Property             | Complexity |
| -------------------- | ---------- |
| **Time Complexity**  | O(E)       |
| **Space Complexity** | O(E)       |

where **E** represents the number of edges in the graph.

---

### Stage 2: Edge List → CSR

| Property             | Complexity |
| -------------------- | ---------- |
| **Time Complexity**  | O(V + E)   |
| **Space Complexity** | O(V + E)   |

where:

- **V** = Number of vertices
- **E** = Number of edges

The CSR conversion traverses all vertices and edges exactly once to construct the `row_ptr`, `col_idx`, and `values` arrays.

---

# Runtime Measurement

The execution time reported in this assignment follows the CS509 Programming Laboratory guidelines.

## GEMM

For both **Simple GEMM** and **Blocking GEMM**, the timer starts immediately before the matrix multiplication algorithm begins and stops immediately after the multiplication completes.

The following operations are **excluded** from the measured execution time:

- Reading the input file
- Matrix creation and memory allocation
- Matrix initialization
- Output formatting
- Printing the matrices and execution results

Only the execution time of the matrix multiplication algorithm is reported.

---

## CSR

For the CSR implementation, the timer starts immediately before the **Edge List → CSR conversion** and stops immediately after the CSR arrays have been generated.

The following preprocessing operations are **not included** in the measured execution time:

- Reading the graph from the input file
- Constructing the adjacency list
- Converting the adjacency list into an edge list
- Printing the adjacency list
- Printing the edge list
- Printing the CSR arrays

Only the CSR conversion algorithm is timed, ensuring that the reported execution time represents the algorithm alone.

---

# References

The following resources were referred to while understanding and implementing the algorithms:

1. Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein, **Introduction to Algorithms (CLRS)**, MIT Press.

2. David A. Patterson and John L. Hennessy, **Computer Organization and Design**, Morgan Kaufmann.

3. Intel Developer Documentation – Cache Optimization and Blocking Techniques for Matrix Multiplication.

4. GeeksforGeeks – General Matrix Multiplication (GEMM).

5. GeeksforGeeks – Compressed Sparse Row (CSR) Representation of Sparse Matrices and Graphs.

6. CS509 Programming Laboratory Lecture Notes and Assignment Specifications.

---

# Conclusion

This assignment demonstrates two important concepts in high-performance and graph computing.

- **General Matrix Multiplication (GEMM)** was implemented using both the Simple and Blocking approaches. Both implementations produce identical results, while Blocking GEMM improves practical performance through better cache utilization.

- **Compressed Sparse Row (CSR)** graph representation was implemented by converting an adjacency-list graph into CSR format. The generated CSR representation provides an efficient storage format for sparse graphs and serves as the foundation for future graph algorithms such as BFS, DFS, and Single Source Shortest Path (SSSP).

The project follows modular software engineering principles by separating algorithms, helper functions, drivers, test cases, and documentation, making the codebase maintainable and extensible for subsequent assignments.
