#include "board.h"

// initializes a board
Board newBoard() {
  Board board;
  // black is always at the top
  for (int i = 0; i < numpcs; i++) {
    board.a[i] = B;
    board.a[i + 20] = W;
  }
  // empty tiles
  for (int i = 12; i < 20; i++) {
    board.a[i] = E;
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
    cout << "  |     |  "<< board.a[i] << "  |     |  " << 
                            board.a[i + 1] << "  |     |  " << 
                            board.a[i + 2] << "  |     |  " <<
                            board.a[i + 3] << "  |" << endl;
    cout << "  |_____|_____|_____|_____|_____|_____|_____|_____|" << endl;
    cout << "  |     |     |     |     |     |     |     |     |" << endl;
    cout << "  |  " << board.a[i + 4] << "  |     |  " << 
                      board.a[i + 5] << "  |     |  " << 
                      board.a[i + 6] << "  |     |  " << 
                      board.a[i + 7] << "  |     |  " << endl;
    cout << "  |_____|_____|_____|_____|_____|_____|_____|_____|" << endl;
  }
  cout << endl;
  cout << "  =================================================" << endl;
}

// creates a copy of a board
Board boardCopy(const Board& board) {
  Board bCopy;
  for (int i = 0; i < bSize; i++) {
    bCopy.a[i] = board.a[i];
  }
  return bCopy;
}


