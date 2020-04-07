#include "commlink.h"
#include "checkalt.h"
#include "minimax.h"

using namespace std;
// main function for AI
// change name to main when running program
// int checkersAI() {
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

    cout << "Chosen difficulty: " << difficulty << endl;

    Board board;
    // now this will loop until the end of the game
    while (comms.getBoardState(board)) {
      comms.sendBoardState(chooseMove(board, difficulty));
    }
    cout << "Game ended! Waiting for Arduino to start a new game...\n";
  }

  return 0;
}
/*
// for testing fucntions
int main() {
  Board board;
  Board move = chooseMove(board, 1000);
  return 0;
}
*/