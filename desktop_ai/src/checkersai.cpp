#include "commlink.h"
#include "checkalt.h"
#include "minimax.h"

using namespace std;
// main function for AI
// change name to main when running program
// int checkersAI() {
int main() {
  // assume Arduino is in /dev/ttyACM0
  // if not, pass the port name as a string on the Commlink initializer
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
      newGame.display();
    }

    cout << "Chance of random move: 1 in " << difficulty << endl;

    Board board;
    // now this will loop until the end of the game
    while (comms.getBoardState(board)) {
      comms.sendBoardState(chooseMove(board, difficulty));
      board.display();
    }
    cout << "Game ended! Waiting for Arduino to start a new game...\n";
  }

  return 0;
}