#include "board.h"

// initializes a board
Board newBoard() {
  Board board;
  // black is always at the top
  for (int i = 0; i < numpcs; i++) {
    board.bArray[i] = B;
    board.bArray[i + 20] = W;
  }
  // empty tiles
  for (int i = 12; i < 20; i++) {
    board.bArray[i] = E;
  }
  return board;
}

// displays board on stdout
void displayBoard(const Board& board) {
  using std::cout;
  using std::endl;

  cout << "  =================================================" << endl;
  cout << "   _______________________________________________" << endl;
  for (int i = 0; i <= 24; i += 8) 
  {
    cout << "  |     |     |     |     |     |     |     |     |" << endl;
    cout << "  |     |  "<< board.bArray[i] << "  |     |  " << 
                            board.bArray[i + 1] << "  |     |  " << 
                            board.bArray[i + 2] << "  |     |  " <<
                            board.bArray[i + 3] << "  |" << endl;
    cout << "  |_____|_____|_____|_____|_____|_____|_____|_____|" << endl;
    cout << "  |     |     |     |     |     |     |     |     |" << endl;
    cout << "  |  " << board.bArray[i + 4] << "  |     |  " << 
                      board.bArray[i + 5] << "  |     |  " << 
                      board.bArray[i + 6] << "  |     |  " << 
                      board.bArray[i + 7] << "  |     |  " << endl;
    cout << "  |_____|_____|_____|_____|_____|_____|_____|_____|" << endl;
  }
  cout << endl;
  cout << "  =================================================" << endl;
}

// creates a copy of a board
Board boardCopy(const Board& board) {
  Board bCopy;
  for (int i = 0; i < 32; i++) {
    bCopy.bArray[i] = board.bArray[i];
  }
  return bCopy;
}
