#include "../include/matrix.h"

//To create a matrix with the given dimensions.(Memory is allocated dynamically and initialized to zero.)
Matrix createMatrix(int rows, int cols)
{
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix.data[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            matrix.data[i][j] = 0;
        }
    }
    return matrix;
}

//To Free all dynamically allocated memory.
void destroyMatrix(Matrix &matrix)
{
    if (matrix.data == nullptr)
        return;
    for (int i = 0; i < matrix.rows; i++)
    {
        delete[] matrix.data[i];
    }
    delete[] matrix.data;
    matrix.data = nullptr;
    matrix.rows = 0;
    matrix.cols = 0;
}

//To read matrix elements from an input file.
void readMatrix(ifstream &inputFile, Matrix &matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            inputFile >> matrix.data[i][j];
        }
    }
}

//Prints the matrix.
void printMatrix(const Matrix &matrix)
{
    for (int i = 0; i < matrix.rows; i++)
    {
        for (int j = 0; j < matrix.cols; j++)
        {
            cout << matrix.data[i][j];
            if (j + 1 < matrix.cols)
                cout << " ";
        }
        cout << '\n';
    }
}