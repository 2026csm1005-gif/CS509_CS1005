#include <stdexcept>
#include <algorithm>
#include "../include/gemm.h"

//Standard triple-loop matrix multiplication.
Matrix simpleGemm(const Matrix &matrixA, const Matrix &matrixB)
{
    //Checking whether multiplication is possible or not.
    if (matrixA.cols != matrixB.rows)
    {
        throw std::invalid_argument("Matrix dimensions are not compatible!!!");
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

Matrix blockingGemm(const Matrix &matrixA, const Matrix &matrixB, int blockSize)
{
    if (matrixA.cols != matrixB.rows)
    {
        throw std::invalid_argument("Matrix dimensions are not compatible!!!");
    }

    Matrix result = createMatrix(matrixA.rows, matrixB.cols);

    for (int ii = 0; ii < matrixA.rows; ii += blockSize)
    {
        for (int jj = 0; jj < matrixB.cols; jj += blockSize)
        {
            for (int kk = 0; kk < matrixA.cols; kk += blockSize)
            {
                int rowLimit = std::min(ii + blockSize, matrixA.rows);
                int colLimit = std::min(jj + blockSize, matrixB.cols);
                int innerLimit = std::min(kk + blockSize, matrixA.cols);

                for (int i = ii; i < rowLimit; i++)
                {
                    for (int j = jj; j < colLimit; j++)
                    {
                        for (int k = kk; k < innerLimit; k++)
                        {
                            result.data[i][j] +=
                                matrixA.data[i][k] *
                                matrixB.data[k][j];
                        }
                    }
                }
            }
        }
    }

    return result;
}