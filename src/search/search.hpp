#ifndef SEARCH_H
#define SEARCH_H
#include <algorithm>
#include <cstdint>
#include <ctime>
#include <future>
#include <iostream>
#include <map>
#include <string>
#include <thread>

#include "../game/game.hpp"

using namespace std;

class Search {
 public:
  uint32_t depth{0};
  uint32_t ply;
  Search(uint32_t d) { depth = d; }
  char root(Game game);
  int32_t negamax(Game game, int32_t dep, int32_t alpha, int32_t beta, int32_t ply);
};

#endif