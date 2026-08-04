#include <iostream>
#include <fstream>
#include <iomanip>

#include "../include/matrix.h"
#include "../include/gemm.h"
#include "../include/timer.h"

using namespace std;

const int BLOCK_SIZE = 32;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: gemm <input_file>\n";
        return 1;
    }
    ifstream inputFile(argv[1]);

    if (!inputFile.is_open())
    {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    int rowsA;
    int colsA;
    int colsB;

    inputFile >> rowsA >> colsA >> colsB;

    Matrix matrixA = createMatrix(rowsA, colsA);
    Matrix matrixB = createMatrix(colsA, colsB);

    readMatrix(inputFile, matrixA);
    readMatrix(inputFile, matrixB);

    inputFile.close();

    // Simple GEMM
    Timer simpleTimer;

    simpleTimer.start();
    Matrix simpleResult = simpleGemm(matrixA, matrixB);
    simpleTimer.stop();

    // Blocking GEMM
    Timer blockingTimer;

    blockingTimer.start();
    Matrix blockingResult = blockingGemm(matrixA, matrixB, BLOCK_SIZE);
    blockingTimer.stop();

    // Displaying Input Matrices for small matrices only.
    if ((matrixA.rows <= 10 && matrixA.cols <= 10) && (matrixB.rows <= 10 && matrixB.cols <= 10))
    {
        cout << "M = " << matrixA.rows << ", K = " << matrixB.rows << ", N = " << matrixB.cols << '\n';
        cout << "Matrix A:\n";
        printMatrix(matrixA);

        cout << "\n";

        cout << "Matrix B:\n";
        printMatrix(matrixB);

        cout << "\n";
    }

    // Displaying Result Matrices for small matrices only.
    if ((matrixA.rows <= 10 && matrixA.cols <= 10) && (matrixB.rows <= 10 && matrixB.cols <= 10))
    {
        cout << "Algorithm: GEMM Simple\n";
        printMatrix(simpleResult);

        cout << "\n";

        cout << "Algorithm: GEMM Blocking\n";
        printMatrix(blockingResult);

        cout << "\n";
    }

    // Verification
    if (!((matrixA.rows <= 10 && matrixA.cols <= 10) && (matrixB.rows <= 10 && matrixB.cols <= 10)))
    {
        cout << "Result matrix is too large to display.\n";
        if (compareMatrices(simpleResult, blockingResult))
        {
            cout << "Result Verification : PASSED\n";
        }
        else
        {
            cout << "Result Verification : FAILED\n";
        }
    }

    // Timing
    cout << fixed << setprecision(6);
    cout << "Simple GEMM Time : "
         << simpleTimer.getElapsedTime()
         << " ms\n";

    cout << "Blocking GEMM Time : "
         << blockingTimer.getElapsedTime()
         << " ms\n";

    // Cleanup
    destroyMatrix(matrixA);
    destroyMatrix(matrixB);
    destroyMatrix(simpleResult);
    destroyMatrix(blockingResult);

    return 0;
}