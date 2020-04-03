#include "commlink.h"
#include "game.h"

int main() {
  CommLink comms; // start communication with Arduino
  std::cout << "Preparing communication... ";
  comms.confirm(); // confirm link with Arduino
  std::cout << "Communication ready!" << std::endl;
  Board board, test;
  for (int i = 0; i < bSize; i++) {
    test.a[i] = E;
  }
  while (true) {
    comms.sendBoardState(test);
    comms.sendBoardState(newBoard());
    if (comms.getBoardState(board)) {
      displayBoard(board);
    }
  }
  
  return 0;
}