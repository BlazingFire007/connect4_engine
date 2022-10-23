#ifndef GAME_H
#define GAME_H
#include "../board/board.hpp"
#include "../board/masks.hpp"

enum Turn { O, X };

class Game {
public:
  Board board;
  Masks masks;
  Turn turn{X};
  std::string history;
  bool place(char col);
  bool undo(char col);
  void load(std::string moves);
  int32_t check_winner();
  int32_t eval(int32_t ply);
  std::string get_moves();
};

#endif