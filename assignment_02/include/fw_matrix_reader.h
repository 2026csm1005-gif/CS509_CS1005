#ifndef FW_MATRIX_READER_H
#define FW_MATRIX_READER_H

#include <istream>
#include <vector>

bool readFloydWarshallMatrix(std::istream &input, std::vector<std::vector<long long>> &matrix);

#endif