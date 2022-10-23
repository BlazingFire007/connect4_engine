#include "./game/game.hpp"
#include "./search/search.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  if (argc > 1) {
    uint8_t depth = stoi(argv[1]);
    Game game;
    Search search(depth);
    game.load(argv[2]);
    char cmove = search.root(game);
    cout << cmove << endl;
    return 0;
  }

  string go_first;
  string depth_input;
  cout << "Would you like to start? (y/n): ";
  cin >> go_first;
  cout << "Select computer search depth (5-11 recommended): ";
  cin >> depth_input;

  go_first = tolower(go_first[0]);
  if (depth_input == "") depth_input = "9";
  uint8_t depth = stoi(depth_input);

  Game game;
  Search search(depth);
  if (go_first == "n") {
    game.place('d');
  }
  cout << endl;

  while (true) {
    game.board.print();
    string input;
    cout << "Enter a move: ";
    cin >> input;

    bool can_place = game.place(input[0]);
    if (!can_place) {
      cout << "Invalid move" << endl;
      continue;
    }

    int32_t winner = game.check_winner();
    if (winner != -1) {
      game.board.print();
      cout << (winner == 1 ? 'X' : 'O') << " wins!" << endl;
      break;
    }
    char cmove = search.root(game);
    game.place(cmove);
    winner = game.check_winner();
    if (winner != -1) {
      game.board.print();
      cout << (winner == 1 ? 'X' : 'O') << " wins!" << endl;
      break;
    }
  }
  return 0;
}