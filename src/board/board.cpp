#include "board.hpp"

#include "../util/util.hpp"
// set bit at position pos to 1 on player's board
bool Board::set(uint32_t player, uint32_t pos) {
  bitboards[player] |= 1ULL << pos;
  board[pos] = true;
  return true;
}
// get bit at position pos on player's board
bool Board::get(uint32_t player, uint32_t pos) { return (bitboards[player] & (1ULL << pos)) != 0; }

// unset a bit at the position. Try on both boards.
bool Board::unset(uint32_t pos) {
  bitboards[0] &= ~(1ULL << pos);
  bitboards[1] &= ~(1ULL << pos);
  board[pos] = false;
  return true;
}

// get the lowest empty position in a column
// return a negative number if the column is full
int32_t Board::lowest(uint32_t col) {
  Bitboard bb = bitboards[0] | bitboards[1];
  uint32_t pos = 0;
  for (int i = 0; i < 6; i++) {
    if ((bb & (1ULL << (col + i * 7))) == 0) {
      pos = col + i * 7;
    }
  }
  if (pos == 0) {
    if (get(0, col) || get(1, col)) {
      std::string scol = std::to_string(col);
      scol.push_back('6');
      int32_t pos = convert_square(scol);
      return pos - 7;
    }
  }
  return pos;
}

// print the board
void Board::print() {
  for (int i = 0; i < 42; i++) {
    if (i % 7 == 0) {
      if (i != 0) {
        std::cout << '|';
      }
      std::cout << "\n|" << 6 - (i / 6 + 1) + 1 << "|: ";
    }
    if (get(1, i) != false) {
      std::cout << "|X";
    } else if (get(0, i) != false) {
      std::cout << "|O";
    } else {
      std::cout << "| ";
    }
  }
  std::cout << '|';
  std::cout << "\n     --------------";
  std::cout << "\n     |A|B|C|D|E|F|G\n" << std::endl;
}
