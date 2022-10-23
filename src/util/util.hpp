#ifndef UTIL_H
#define UTIL_H
#include <cstdint>
#include <string>
uint32_t convert_col(char col);
uint32_t convert_row(char row);
char convert_col_back(uint32_t col);
uint32_t convert_square(std::string square);

#endif