#include "game.hpp"
#include "../util/util.hpp"

bool Game::place(char col) {
  uint32_t col_pos = convert_col(col);
  int player = turn;
  int32_t can_set = board.lowest(col_pos);
  if (can_set < 0)
    return false;
  board.set(player, can_set);
  turn = player == 0 ? X : O;
  history.push_back(col);
  return true;
}

bool Game::undo(char col) {
  uint32_t col_pos = convert_col(col);
  int32_t can_unset = board.lowest(col_pos);
  board.unset(can_unset + 7);
  turn = turn == 0 ? X : O;
  history.pop_back();
  return true;
}

void Game::load(std::string moves) {
  for (char c : moves) {
    place(c);
  }
}

int32_t Game::check_winner() {
  Turn player = turn;
  Turn opp_player = player == 0 ? X : O;

  Bitboard player_board = board.bitboards[player];
  Bitboard opp_board = board.bitboards[opp_player];

  bool player_won = masks.check_win(player_board);
  bool opp_won = masks.check_win(opp_board);

  if (player_won)
    return player;
  else if (opp_won)
    return opp_player;
  else
    return -1;
}

int32_t Game::eval(int32_t ply) {
  Turn player = turn;
  Turn opp_player = player == 0 ? X : O;

  int32_t winner = check_winner();

  int32_t score = 0;
  if (winner == opp_player) {
    score -= 100;
  } else if (winner == player) {
    score += 100;
  }
  score += ply;
  return score;
}

std::string Game::get_moves() {
  using namespace std;
  std::string moves;
  for (int i = 0; i < 7; i++) {
    if (board.lowest(i) >= 0) {
      moves.push_back(convert_col_back(i));
    }
  }
  return moves;
}