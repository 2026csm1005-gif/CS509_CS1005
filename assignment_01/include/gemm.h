#ifndef GEMM_H
#define GEMM_H

#include "matrix.h"

//Performs standard matrix multiplication and returns resultant matrix.
Matrix simpleGemm(const Matrix &matrixA, const Matrix &matrixB);

//Performs cache-friendly blocked matrix multiplication. (blockSize : Size of each tile/block.)
Matrix blockingGemm(const Matrix &matrixA, const Matrix &matrixB, int blockSize);
#endif