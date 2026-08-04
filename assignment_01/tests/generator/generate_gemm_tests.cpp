#include <fstream>
#include <iostream>

using namespace std;

void generateTestFile(const string &fileName, int rowsA, int colsA, int colsB)
{
    ofstream file(fileName);

    if (!file.is_open())
    {
        cout << "Unable to create file.\n";
        return;
    }

    file << rowsA << " " << colsA << " " << colsB << "\n\n";

    int value = 1;

    // Matrix A
    for (int i = 0; i < rowsA; i++)
    {
        for (int j = 0; j < colsA; j++)
        {
            file << value++ << " ";
        }
        file << "\n";
    }

    file << "\n";

    value = 1;

    // Matrix B
    for (int i = 0; i < colsA; i++)
    {
        for (int j = 0; j < colsB; j++)
        {
            file << value++ << " ";
        }
        file << "\n";
    }

    file.close();

    cout << fileName << " generated successfully.\n";
}

int main()
{
    generateTestFile("tests/gemm/gemm_test_07.txt", 10, 10, 10);

    generateTestFile("tests/gemm/gemm_test_08.txt", 100, 100, 100);

    generateTestFile("tests/gemm/gemm_test_09.txt", 250, 250, 250);

    generateTestFile("tests/gemm/gemm_test_10.txt", 500, 500, 500);

    return 0;
}