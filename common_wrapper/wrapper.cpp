#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

// Utility: check whether a file exists
bool fileExists(const string &path)
{
    return fs::exists(path);
}

// Compile a command and report the result
bool compileCommand(const string &description, const string &command)
{
    cout << "\n-----------------------------------------\n";
    cout << "Compiling: " << description << '\n';
    cout << "-----------------------------------------\n";
    int result = system(command.c_str());
    if (result != 0)
    {
        cout << "Error: Compilation failed for " << description << ".\n";
        return false;
    }
    cout << "Compilation successful: " << description << '\n';
    return true;
}

// Assignment 1 compilation
bool compileAssignment1()
{
    cout << "\n=========================================\n";
    cout << "        COMPILING ASSIGNMENT 1\n";
    cout << "=========================================\n";
    bool allSuccessful = true;
    // GEMM
    if (!fileExists("assignment_01/driver/gemm_driver.cpp") || !fileExists("assignment_01/src/gemm.cpp") || !fileExists("assignment_01/src/matrix.cpp") || !fileExists("assignment_01/src/timer.cpp"))
    {
        cout << "Error: Required GEMM source file is unavailable.\n";
        allSuccessful = false;
    }
    else
    {
        string command = "g++ assignment_01/driver/gemm_driver.cpp assignment_01/src/gemm.cpp assignment_01/src/matrix.cpp assignment_01/src/timer.cpp -o gemm_driver.exe";
        if (!compileCommand("Assignment 1 - GEMM", command))
            allSuccessful = false;
    }
    // CSR
    if (!fileExists("assignment_01/driver/csr_driver.cpp") || !fileExists("assignment_01/src/csr.cpp") || !fileExists("assignment_01/src/graph.cpp") || !fileExists("assignment_01/src/edge.cpp") || !fileExists("assignment_01/src/timer.cpp"))
    {
        cout << "Error: Required CSR source file is unavailable.\n";
        allSuccessful = false;
    }
    else
    {
        string command = "g++ assignment_01/driver/csr_driver.cpp assignment_01/src/csr.cpp assignment_01/src/graph.cpp assignment_01/src/edge.cpp assignment_01/src/timer.cpp -o csr_driver.exe";
        if (!compileCommand("Assignment 1 - CSR", command))
            allSuccessful = false;
    }
    return allSuccessful;
}

// Assignment 2 compilation
bool compileAssignment2()
{
    cout << "\n=========================================\n";
    cout << "        COMPILING ASSIGNMENT 2\n";
    cout << "=========================================\n";
    bool allSuccessful = true;
    // Bellman-Ford
    if (!fileExists("assignment_02/driver/bf_driver.cpp") || !fileExists("assignment_02/src/bellman_ford.cpp") || !fileExists("assignment_02/src/bf_graph_reader.cpp") || !fileExists("assignment_01/src/csr.cpp") || !fileExists("assignment_01/src/graph.cpp") || !fileExists("assignment_01/src/edge.cpp") || !fileExists("assignment_01/src/timer.cpp"))
    {
        cout << "Error: Required Bellman-Ford source file is unavailable.\n";
        allSuccessful = false;
    }
    else
    {
        string command = "g++ assignment_02/driver/bf_driver.cpp assignment_02/src/bellman_ford.cpp assignment_02/src/bf_graph_reader.cpp assignment_01/src/csr.cpp assignment_01/src/graph.cpp assignment_01/src/edge.cpp assignment_01/src/timer.cpp -o bf_driver.exe";
        if (!compileCommand("Assignment 2 - Bellman-Ford", command))
            allSuccessful = false;
    }
    // Floyd-Warshall
    if (!fileExists("assignment_02/driver/fw_driver.cpp") || !fileExists("assignment_02/src/floyd_warshall.cpp") || !fileExists("assignment_02/src/fw_matrix_reader.cpp") || !fileExists("assignment_01/src/timer.cpp"))
    {
        cout << "Error: Required Floyd-Warshall source file is unavailable.\n";
        allSuccessful = false;
    }
    else
    {
        string command = "g++ assignment_02/driver/fw_driver.cpp assignment_02/src/floyd_warshall.cpp assignment_02/src/fw_matrix_reader.cpp assignment_01/src/timer.cpp -o fw_driver.exe";
        if (!compileCommand("Assignment 2 - Floyd-Warshall", command))
        {
            allSuccessful = false;
        }
    }
    return allSuccessful;
}

// Assignment 3 compilation
bool compileAssignment3(bool includeGenerator = true)
{
    cout << "\n=========================================\n";
    cout << "        COMPILING ASSIGNMENT 3\n";
    cout << "=========================================\n";

    bool allSuccessful = true;

    // Kruskal MST
    if (!fileExists("assignment_03/driver/kruskal_driver.cpp") ||
        !fileExists("assignment_03/src/kruskal.cpp") ||
        !fileExists("assignment_03/src/dsu.cpp") ||
        !fileExists("assignment_03/src/mst_graph_reader.cpp") ||
        !fileExists("assignment_01/src/csr.cpp") ||
        !fileExists("assignment_01/src/graph.cpp") ||
        !fileExists("assignment_01/src/edge.cpp") ||
        !fileExists("assignment_01/src/timer.cpp"))
    {
        cout << "Error: Required Kruskal source file is unavailable.\n";
        allSuccessful = false;
    }
    else
    {
        string command =
            "g++ assignment_03/driver/kruskal_driver.cpp "
            "assignment_03/src/kruskal.cpp "
            "assignment_03/src/dsu.cpp "
            "assignment_03/src/mst_graph_reader.cpp "
            "assignment_01/src/csr.cpp "
            "assignment_01/src/graph.cpp "
            "assignment_01/src/edge.cpp "
            "assignment_01/src/timer.cpp "
            "-o kruskal_driver.exe";

        if (!compileCommand("Assignment 3 - Kruskal MST", command))
            allSuccessful = false;
    }

    // Prim MST
    if (!fileExists("assignment_03/driver/prim_driver.cpp") ||
        !fileExists("assignment_03/src/prim.cpp") ||
        !fileExists("assignment_03/src/mst_graph_reader.cpp") ||
        !fileExists("assignment_01/src/csr.cpp") ||
        !fileExists("assignment_01/src/graph.cpp") ||
        !fileExists("assignment_01/src/edge.cpp") ||
        !fileExists("assignment_01/src/timer.cpp"))
    {
        cout << "Error: Required Prim source file is unavailable.\n";
        allSuccessful = false;
    }
    else
    {
        string command =
            "g++ assignment_03/driver/prim_driver.cpp "
            "assignment_03/src/prim.cpp "
            "assignment_03/src/mst_graph_reader.cpp "
            "assignment_01/src/csr.cpp "
            "assignment_01/src/graph.cpp "
            "assignment_01/src/edge.cpp "
            "assignment_01/src/timer.cpp "
            "-o prim_driver.exe";

        if (!compileCommand("Assignment 3 - Prim MST", command))
            allSuccessful = false;
    }

    // MST Test Generator (compile only when requested)
    if (includeGenerator)
    {
        if (!fileExists("assignment_03/utilities/generate_mst_tests.cpp"))
        {
            cout << "Error: MST generator source file is unavailable.\n";
            allSuccessful = false;
        }
        else
        {
            string command =
                "g++ -std=c++17 assignment_03/utilities/generate_mst_tests.cpp "
                "-o generate_mst_tests.exe";

            if (!compileCommand("Assignment 3 - MST Test Generator", command))
                allSuccessful = false;
        }
    }

    return allSuccessful;
}

// Display available algorithms
void displayAlgorithms()
{
    cout << "\n=========================================\n";
    cout << "       AVAILABLE ALGORITHMS\n";
    cout << "=========================================\n";

    cout << "\nAssignment 1\n";
    cout << "  1. GEMM\n";
    cout << "  2. CSR\n";

    cout << "\nAssignment 2\n";
    cout << "  3. Bellman-Ford\n";
    cout << "  4. Floyd-Warshall\n";

    cout << "\nAssignment 3\n";
    cout << "  5. Kruskal MST\n";
    cout << "  6. Prim MST\n";

    cout << "\n=========================================\n";
}

// Get test files from a directory
vector<string> getTestFiles(const string &directory)
{
    vector<string> files;

    if (!fs::exists(directory))
    {
        return files;
    }

    for (const auto &entry : fs::directory_iterator(directory))
    {
        if (entry.is_regular_file() &&
            entry.path().extension() == ".txt")
        {
            files.push_back(entry.path().string());
        }
    }

    sort(files.begin(), files.end());

    return files;
}

// Get information for an algorithm
bool getAlgorithmInfo(
    int choice,
    string &algorithmName,
    string &testDirectory,
    string &executable)
{
    switch (choice)
    {
    case 1:
        algorithmName = "GEMM";
        testDirectory = "assignment_01/tests/gemm";
        executable = "gemm_driver.exe";
        return true;

    case 2:
        algorithmName = "CSR";
        testDirectory = "assignment_01/tests/csr";
        executable = "csr_driver.exe";
        return true;

    case 3:
        algorithmName = "Bellman-Ford";
        testDirectory = "assignment_02/tests/bellman_ford";
        executable = "bf_driver.exe";
        return true;

    case 4:
        algorithmName = "Floyd-Warshall";
        testDirectory = "assignment_02/tests/floyd_warshall";
        executable = "fw_driver.exe";
        return true;

    case 5:
        algorithmName = "Kruskal MST";
        testDirectory = "assignment_03/tests/mst";
        executable = "kruskal_driver.exe";
        return true;

    case 6:
        algorithmName = "Prim MST";
        testDirectory = "assignment_03/tests/mst";
        executable = "prim_driver.exe";
        return true;

    default:
        return false;
    }
}

// Run one selected test
void runOneTest()
{
    int choice;

    cout << "\n=========================================\n";
    cout << "          SELECT ALGORITHM\n";
    cout << "=========================================\n";

    cout << "1. GEMM\n";
    cout << "2. CSR\n";
    cout << "3. Bellman-Ford\n";
    cout << "4. Floyd-Warshall\n";
    cout << "5. Kruskal MST\n";
    cout << "6. Prim MST\n";
    cout << "7. Back\n";

    cout << "\nEnter choice: ";

    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: Invalid input.\n";
        return;
    }

    if (choice == 7)
        return;

    string algorithmName;
    string testDirectory;
    string executable;

    if (!getAlgorithmInfo(choice,
                          algorithmName,
                          testDirectory,
                          executable))
    {
        cout << "Error: Invalid algorithm choice.\n";
        return;
    }

    if (!fileExists(executable))
    {
        cout << "Error: Executable unavailable: "
             << executable << '\n';
        cout << "Please compile the corresponding assignment first.\n";
        return;
    }

    vector<string> testFiles = getTestFiles(testDirectory);

    if (testFiles.empty())
    {
        cout << "Error: No test files found in: "
             << testDirectory << '\n';
        return;
    }

    cout << "\nAvailable " << algorithmName << " test files:\n\n";

    for (size_t i = 0; i < testFiles.size(); i++)
    {
        cout << i + 1 << ". "
             << fs::path(testFiles[i]).filename().string()
             << '\n';
    }

    cout << testFiles.size() + 1 << ". Back\n";

    int testChoice;

    cout << "\nEnter choice: ";

    if (!(cin >> testChoice))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: Invalid input.\n";
        return;
    }

    if (testChoice == static_cast<int>(testFiles.size()) + 1)
        return;

    if (testChoice < 1 ||
        testChoice > static_cast<int>(testFiles.size()))
    {
        cout << "Error: Invalid test selection.\n";
        return;
    }

    string selectedTest = testFiles[testChoice - 1];

    cout << "\n=========================================\n";
    cout << "Running: " << algorithmName << '\n';
    cout << "Test   : "
         << fs::path(selectedTest).filename().string()
         << '\n';
    cout << "=========================================\n";

    string command =
        executable + " \"" + selectedTest + "\"";

    int result = system(command.c_str());

    if (result != 0)
        cout << "\nError: Test execution failed.\n";
    else
        cout << "\nTest completed successfully.\n";
}

// Run all tests for one algorithm
bool runAllAlgorithmTests(
    const string &algorithmName,
    const string &testDirectory,
    const string &executable)
{
    cout << "\n=========================================\n";
    cout << "Running all tests: " << algorithmName << '\n';
    cout << "=========================================\n";

    // Check executable
    if (!fileExists(executable))
    {
        cout << "Error: Executable unavailable: "
             << executable << '\n';

        cout << "Please compile the corresponding "
                "assignment first.\n";

        return false;
    }

    // Get all test files
    vector<string> testFiles =
        getTestFiles(testDirectory);

    if (testFiles.empty())
    {
        cout << "Error: No test files found in: "
             << testDirectory << '\n';

        return false;
    }

    int passed = 0;
    int failed = 0;

    for (size_t i = 0; i < testFiles.size(); i++)
    {
        string filename =
            fs::path(testFiles[i]).filename().string();

        cout << "\n-----------------------------------------\n";
        cout << "Test " << i + 1
             << "/" << testFiles.size()
             << " : " << filename << '\n';
        cout << "-----------------------------------------\n";

        string command =
            executable + " \"" + testFiles[i] + "\"";

        int result = system(command.c_str());

        if (result == 0)
        {
            cout << "\nStatus: PASS\n";
            passed++;
        }
        else
        {
            cout << "\nStatus: FAIL\n";
            failed++;
        }
    }

    cout << "\n=========================================\n";
    cout << algorithmName << " Test Summary\n";
    cout << "=========================================\n";

    cout << "Total tests : " << testFiles.size() << '\n';
    cout << "Passed      : " << passed << '\n';
    cout << "Failed      : " << failed << '\n';

    if (failed == 0)
    {
        cout << "Result      : ALL TESTS PASSED\n";
    }
    else
    {
        cout << "Result      : SOME TESTS FAILED\n";
    }

    cout << "=========================================\n";

    return failed == 0;
}

// Run all tests for Assignment 1
bool runAllAssignment1Tests()
{
    bool success = true;

    cout << "\n=========================================\n";
    cout << "       RUNNING ASSIGNMENT 1 TESTS\n";
    cout << "=========================================\n";

    if (!runAllAlgorithmTests(
            "GEMM",
            "assignment_01/tests/gemm",
            "gemm_driver.exe"))
    {
        success = false;
    }

    if (!runAllAlgorithmTests(
            "CSR",
            "assignment_01/tests/csr",
            "csr_driver.exe"))
    {
        success = false;
    }

    return success;
}

// Run all tests for Assignment 2
bool runAllAssignment2Tests()
{
    bool success = true;

    cout << "\n=========================================\n";
    cout << "       RUNNING ASSIGNMENT 2 TESTS\n";
    cout << "=========================================\n";

    if (!runAllAlgorithmTests(
            "Bellman-Ford",
            "assignment_02/tests/bellman_ford",
            "bf_driver.exe"))
    {
        success = false;
    }

    if (!runAllAlgorithmTests(
            "Floyd-Warshall",
            "assignment_02/tests/floyd_warshall",
            "fw_driver.exe"))
    {
        success = false;
    }

    return success;
}

// Run all tests for Assignment 3
bool runAllAssignment3Tests()
{
    bool success = true;

    cout << "\n=========================================\n";
    cout << "       RUNNING ASSIGNMENT 3 TESTS\n";
    cout << "=========================================\n";

    if (!runAllAlgorithmTests(
            "Kruskal MST",
            "assignment_03/tests/mst",
            "kruskal_driver.exe"))
    {
        success = false;
    }

    if (!runAllAlgorithmTests(
            "Prim MST",
            "assignment_03/tests/mst",
            "prim_driver.exe"))
    {
        success = false;
    }

    return success;
}

// Select assignment and run all tests
void runAllTestsForAssignment()
{
    int choice;

    cout << "\n=========================================\n";
    cout << "          SELECT ASSIGNMENT\n";
    cout << "=========================================\n";

    cout << "1. Assignment 1\n";
    cout << "2. Assignment 2\n";
    cout << "3. Assignment 3\n";
    cout << "4. Back\n";

    cout << "\nEnter choice: ";

    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: Invalid input.\n";
        return;
    }

    if (choice == 4)
        return;

    bool success = false;

    switch (choice)
    {
    case 1:
        success = runAllAssignment1Tests();
        break;

    case 2:
        success = runAllAssignment2Tests();
        break;

    case 3:
        success = runAllAssignment3Tests();
        break;

    default:
        cout << "Error: Invalid assignment choice.\n";
        return;
    }

    cout << "\n=========================================\n";

    if (success)
        cout << "All tests for the selected assignment completed successfully.\n";
    else
        cout << "Some tests for the selected assignment failed.\n";

    cout << "=========================================\n";
}

// Run all submitted algorithms
void runAllSubmittedAlgorithms()
{
    cout << "\n=========================================\n";
    cout << "       RUNNING ALL SUBMITTED ALGORITHMS\n";
    cout << "=========================================\n";

    bool allSuccessful = true;

    // Assignment 1 - GEMM
    if (!runAllAlgorithmTests(
            "GEMM",
            "assignment_01/tests/gemm",
            "gemm_driver.exe"))
    {
        allSuccessful = false;
    }

    // Assignment 1 - CSR
    if (!runAllAlgorithmTests(
            "CSR",
            "assignment_01/tests/csr",
            "csr_driver.exe"))
    {
        allSuccessful = false;
    }

    // Assignment 2 - Bellman-Ford
    if (!runAllAlgorithmTests(
            "Bellman-Ford",
            "assignment_02/tests/bellman_ford",
            "bf_driver.exe"))
    {
        allSuccessful = false;
    }

    // Assignment 2 - Floyd-Warshall
    if (!runAllAlgorithmTests(
            "Floyd-Warshall",
            "assignment_02/tests/floyd_warshall",
            "fw_driver.exe"))
    {
        allSuccessful = false;
    }

    // Assignment 3 - Kruskal MST
    if (!runAllAlgorithmTests(
            "Kruskal MST",
            "assignment_03/tests/mst",
            "kruskal_driver.exe"))
    {
        allSuccessful = false;
    }

    // Assignment 3 - Prim MST
    if (!runAllAlgorithmTests(
            "Prim MST",
            "assignment_03/tests/mst",
            "prim_driver.exe"))
    {
        allSuccessful = false;
    }

    cout << "\n=========================================\n";
    cout << "       ALL ALGORITHMS SUMMARY\n";
    cout << "=========================================\n";

    if (allSuccessful)
    {
        cout << "Result: ALL SUBMITTED ALGORITHMS COMPLETED SUCCESSFULLY\n";
    }
    else
    {
        cout << "Result: SOME ALGORITHMS OR TESTS FAILED\n";
    }

    cout << "=========================================\n";
}

// Compile assignment selection
void compileAssignment()
{
    int choice;

    cout << "\n=========================================\n";
    cout << "          SELECT ASSIGNMENT\n";
    cout << "=========================================\n";

    cout << "1. Assignment 1\n";
    cout << "2. Assignment 2\n";
    cout << "3. Assignment 3\n";
    cout << "4. Back\n";

    cout << "\nEnter choice: ";

    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Error: Invalid input.\n";
        return;
    }

    bool success = false;

    switch (choice)
    {
    case 1:
        success = compileAssignment1();
        break;

    case 2:
        success = compileAssignment2();
        break;

    case 3:
        success = compileAssignment3();
        break;

    case 4:
        return;

    default:
        cout << "Error: Invalid assignment choice.\n";
        return;
    }

    cout << '\n';

    if (success)
    {
        cout << "Assignment compilation completed successfully.\n";
    }
    else
    {
        cout << "Assignment compilation completed with errors.\n";
    }
}

// Compile all assignments
void compileAllAssignments()
{
    cout << "\n=========================================\n";
    cout << "         COMPILING ALL ASSIGNMENTS\n";
    cout << "=========================================\n";

    bool assignment1Success = compileAssignment1();
    bool assignment2Success = compileAssignment2();
    bool assignment3Success = compileAssignment3(false);

    cout << "\n=========================================\n";
    cout << "        OVERALL COMPILATION STATUS\n";
    cout << "=========================================\n";

    cout << "Assignment 1 : "
         << (assignment1Success ? "SUCCESS" : "FAILED")
         << '\n';

    cout << "Assignment 2 : "
         << (assignment2Success ? "SUCCESS" : "FAILED")
         << '\n';

    cout << "Assignment 3 : "
         << (assignment3Success ? "SUCCESS" : "FAILED")
         << '\n';

    if (assignment1Success &&
        assignment2Success &&
        assignment3Success)
    {
        cout << "\nResult: ALL ASSIGNMENTS COMPILED SUCCESSFULLY\n";
    }
    else
    {
        cout << "\nResult: SOME ASSIGNMENTS FAILED TO COMPILE\n";
    }

    cout << "=========================================\n";
}

// Main Function
int main()
{
    int choice;

    while (true)
    {
        cout << "\n=========================================\n";
        cout << "          COMMON ASSIGNMENT WRAPPER\n";
        cout << "=========================================\n";

        cout << "1. Display available algorithms\n";
        cout << "2. Compile an assignment\n";
        cout << "3. Run one selected test file\n";
        cout << "4. Run all test files for an assignment\n";
        cout << "5. Compile all assignments\n";
        cout << "6. Run all submitted algorithms\n";
        cout << "7. Exit\n";

        cout << "\nEnter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Error: Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            displayAlgorithms();
            break;

        case 2:
            compileAssignment();
            break;

        case 3:
            runOneTest();
            break;

        case 4:
            runAllTestsForAssignment();
            break;

        case 5:
            compileAllAssignments();
            break;

        case 6:
            runAllSubmittedAlgorithms();
            break;

        case 7:
            cout << "\nExiting wrapper...\n";
            return 0;

        default:
            cout << "\nError: Invalid menu choice.\n";
            break;
        }
    }
}