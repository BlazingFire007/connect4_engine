#include "util.hpp"
#include <iostream>

uint32_t convert_col(char col) {
  col = toupper(col);
  return col >= 'A' and col <= 'G' ? col - 'A' : 0;
}

uint32_t convert_row(char row) {
  return 5 - (row >= '1' and row <= '6' ? row - '1' : 0);
}

char convert_col_back(uint32_t col) {
  return col >= 0 and col <= 6 ? col + 'A' : 'A';
}

uint32_t convert_square(std::string square) {
  char col = square[0];
  char row = square[1];
  uint32_t col_index = convert_col(col);
  uint32_t row_index = convert_row(row);
  return col_index + row_index * 7;
}