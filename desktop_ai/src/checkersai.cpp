#include "commlink.h"
#include "game.h"
#include "checkalt.h"
using namespace std;
// testing some stuff
int main() {
  Board board = Board("00000000011000400110000000000000");
  cout << "oof\n";
  board.display();

  bList list = boardStates(board, true);
  if (!list.empty()) {
    for (auto b : list) {
      b.display();
    }
  }
  
  return 0;
}