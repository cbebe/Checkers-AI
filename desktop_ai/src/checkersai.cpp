#include "commlink.h"
#include "game.h"

int main() {
  CommLink comms; // start communication with Arduino
  std::cout << "Preparing communication... ";
  comms.confirm(); // confirm link with Arduino
  std::cout << "Communication ready!" << std::endl;
  Board board, test;

  while (true) {
    comms.sendBoardState(test);
    if (comms.getBoardState(&board)) {
      board.displayBoard();
    }
  }
  
  return 0;
}