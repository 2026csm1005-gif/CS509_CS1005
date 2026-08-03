#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>

using namespace std;


//Rows represents No. of rows, cols represent No. of columns and data represent Dynamically allocated 2D array.
struct Matrix
{
    int rows;
    int cols;
    int **data;
};

//Matrix utility functions.
Matrix createMatrix(int rows, int cols);
void destroyMatrix(Matrix &matrix);
void readMatrix(ifstream &inputFile, Matrix &matrix);
void printMatrix(const Matrix &matrix);

#endif