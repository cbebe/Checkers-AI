#include "commlink.h"
#include "game.h"

int main() {
  CommLink comms; // start communication with Arduino
  std::cout << "Communication ready!" << std::endl;
  Board board;
  while (true) {
    if (comms.getBoardState(board)) {
      displayBoard(board);
    }

  }
  
  return 0;
}