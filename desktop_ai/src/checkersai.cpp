#include "commlink.h"
#include "game.h"
#include "checkalt.h"

// testing some stuff
int main() {
  Board board;
  bList list = boardStates(board, true);
  for (auto b : list) {
    b.display();
  }
  
  return 0;
}