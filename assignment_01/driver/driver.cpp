#include <iostream>
#include <fstream>

#include "../include/matrix.h"
#include "../include/gemm.h"
#include "../include/timer.h"

using namespace std;

int main()
{
    ifstream inputFile("tests/gemm/gemm_test_01.txt");

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

    Timer timer;

    timer.start();

    Matrix result = simpleGemm(matrixA, matrixB);

    timer.stop();

    cout << "Matrix A\n";
    printMatrix(matrixA);

    cout << '\n';

    cout << "Matrix B\n";
    printMatrix(matrixB);

    cout << '\n';

    cout << "Resultant Matrix\n";
    printMatrix(result);

    cout << '\n';

    cout << "Execution Time: "
         << timer.getElapsedTime()
         << " ms" << endl;

    destroyMatrix(matrixA);
    destroyMatrix(matrixB);
    destroyMatrix(result);

    return 0;
}