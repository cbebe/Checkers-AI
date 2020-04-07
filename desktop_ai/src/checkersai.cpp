#include "commlink.h"
#include "game.h"
#include "checkalt.h"
using namespace std;
// testing some stuff
int main() {
  CommLink comms; // start communication with Arduino
  cout << "Preparing communication... ";
  comms.confirm();
  cout << "Done!\n";
  
  while (true) {
    int difficulty;
    // send a random move if the bot is playing first
    if (comms.startGame(difficulty)) {
      Board newGame = Board(newBoard);
      // send a move to the Arduino
      comms.sendBoardState(chooseMove(newGame, 1));
    }
    Board board;
    // now this will loop until the end of the game
    while (comms.getBoardState(board)) {
      comms.sendBoardState(chooseMove(board, difficulty));
    }
  }

  return 0;
}