#ifndef BOARD_H
#define BOARD_H

#include <iostream>
typedef uint64_t Bitboard;
typedef bool Position[42];

class Board {
public:
  Bitboard bitboards[2]{0};
  Position board{0};
  bool set(uint32_t player, uint32_t pos);
  bool get(uint32_t player, uint32_t pos);
  bool unset(uint32_t pos);
  int32_t lowest(uint32_t col);
  void print();
};

#endif