#include "search.hpp"

char Search::root(Game game) {
  srand(unsigned(time(0)));

  string moves = game.get_moves();
  random_shuffle(moves.begin(), moves.end());

  int32_t alpha = -10000;
  int32_t beta = 10000;
  char best_move;
  int32_t best_score = -10000;

  map<char, future<int32_t>> futures;

  for (char move : moves) {
    game.place(move);
    Game g;
    g.load(game.history);
    futures[move] = std::async(std::launch::async, &Search::negamax, this, g, depth, alpha, beta, ply + 1);
    game.undo(move);
  }

  for (char move : moves) {
    int32_t cur = -futures.at(move).get();
    if (cur > best_score) {
      best_score = cur;
      best_move = move;
      if (best_score > alpha) {
        alpha = best_score;
        if (best_score >= beta) return best_move;
      }
    }
  }

  return best_move;
}

int32_t Search::negamax(Game game, int32_t dep, int32_t alpha, int32_t beta, int32_t ply) {
  if (dep == 0) return game.eval(ply);
  if (game.check_winner() != -1) {
    return -100 + ply;
  }

  int32_t best_score = -10000;
  std::string moves = game.get_moves();
  for (char move : moves) {
    game.place(move);
    Game g;
    g.load(game.history);
    int32_t score = -negamax(g, dep - 1, -beta, -alpha, ply + 1);
    game.undo(move);
    if (score > best_score) {
      best_score = score;
      if (score > alpha) {
        alpha = score;
        if (score >= beta) return best_score;
      }
    }
  }
  return best_score;
}
