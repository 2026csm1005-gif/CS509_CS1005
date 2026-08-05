#include <cstdlib>
// #include <filesystem>
#include <fstream>
#include <direct.h>

#include <iostream>
#include <string>

using namespace std;
bool fileExists(const string &path)
{
    ifstream file(path);
    return file.good();
}

int main()
{

    char currentDirectory[1024];
    _getcwd(currentDirectory, sizeof(currentDirectory));

    cout << "Current Directory: " << currentDirectory << endl;
    int choice;

    while (true)
    {
        cout << "\n=========================================\n";
        cout << "      CS509 Assignment Wrapper\n";
        cout << "=========================================\n";
        cout << "1. Compile GEMM Driver\n";
        cout << "2. Run GEMM (Single Test)\n";
        cout << "3. Run GEMM (All Tests)\n";
        cout << "4. Compile CSR Driver\n";
        cout << "5. Run CSR (Single Test)\n";
        cout << "6. Run CSR (All Tests)\n";
        cout << "7. Compile All\n";
        cout << "8. Exit\n";
        cout << "-----------------------------------------\n";
        cout << "Enter Choice : ";

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "\nCompiling GEMM Driver...\n";
            int status = system("g++ assignment_01/driver/gemm_driver.cpp assignment_01/src/matrix.cpp assignment_01/src/gemm.cpp assignment_01/src/timer.cpp -o gemm_driver.exe");
            if (status == 0)
            {
                cout << "GEMM Driver compiled successfully.\n";
            }
            else
            {
                cout << "Compilation failed.\n";
            }
            break;
        }

        case 2:
        {
            string file;
            cout << "Enter GEMM test file : ";
            cin >> file;

            if (!fileExists(file))
            {
                cout << "Test file not found.\n";
                break;
            }

            string command = "gemm_driver.exe " + file;
            system(command.c_str());
            break;
        }

        case 3:

            for (int i = 1; i <= 10; i++)
            {
                string command =
                    "gemm_driver.exe assignment_01/tests/gemm/gemm_test_0" +
                    to_string(i) + ".txt";

                system(command.c_str());
            }

            break;

        case 4:

        {
            cout << "\nCompiling CSR Driver...\n";
            int status = system("g++ assignment_01/driver/csr_driver.cpp assignment_01/src/graph.cpp assignment_01/src/edge.cpp assignment_01/src/csr.cpp assignment_01/src/timer.cpp -o csr_driver.exe");
            if (status == 0)
            {
                cout << "CSR Driver compiled successfully.\n";
            }
            else
            {
                cout << "Compilation failed.\n";
            }
            break;
        }

        case 5:
        {
            string file;
            cout << "Enter CSR test file : ";
            cin >> file;

            if (!fileExists(file))
            {
                cout << "Test file not found.\n";
                break;
            }

            string command = "csr_driver.exe " + file;

            system(command.c_str());

            break;
        }

        case 6:
        {
            for (int i = 1; i <= 10; i++)
            {
                string command =
                    "csr_driver.exe assignment_01/tests/csr/csr_test_0" +
                    to_string(i) + ".txt";

                system(command.c_str());
            }

            break;
        }
        case 7:
        {
            cout << "\nCompiling all drivers...\n";
            int gemmStatus = system("g++ assignment_01/driver/gemm_driver.cpp assignment_01/src/matrix.cpp assignment_01/src/gemm.cpp assignment_01/src/timer.cpp -o gemm_driver.exe");
            int csrStatus = system("g++ assignment_01/driver/csr_driver.cpp assignment_01/src/graph.cpp assignment_01/src/edge.cpp assignment_01/src/csr.cpp assignment_01/src/timer.cpp -o csr_driver.exe");
            if (gemmStatus == 0 && csrStatus == 0)
            {
                cout << "All drivers compiled successfully.\n";
            }
            else
            {
                cout << "One or more compilations failed.\n";
            }
            break;
        }
        case 8:

            return 0;

        default:

            cout << "Invalid Choice.\n";
        }
    }
}