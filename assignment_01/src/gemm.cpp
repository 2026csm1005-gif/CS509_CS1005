#include <stdexcept>
#include "../include/gemm.h"

//Standard triple-loop matrix multiplication.
Matrix simpleGemm(const Matrix &matrixA, const Matrix &matrixB)
{
    //Checking whether multiplication is possible or not.
    if (matrixA.cols != matrixB.rows)
    {
        throw std::invalid_argument("Matrix dimensions are not compatible.");
    }

    //Create result matrix
    Matrix result = createMatrix(matrixA.rows, matrixB.cols);

    //Standard GEMM implementation
    for (int i = 0; i < matrixA.rows; i++)
    {
        for (int j = 0; j < matrixB.cols; j++)
        {
            for (int k = 0; k < matrixA.cols; k++)
            {
                result.data[i][j] += matrixA.data[i][k] * matrixB.data[k][j];
            }
        }
    }
    return result;
}