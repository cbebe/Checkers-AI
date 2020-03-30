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
Board copy(const Board& board) {
  Board boardCopy;
  for (int i = 0; i < 32; i++) {
    boardCopy.bArray[i] = board.bArray[i];
  }
  return boardCopy;
}

// returns a list of possible board moves
std::list<Board> possibleMoves(const Board& board, piece player) {
  std::list<Board> moves;
  Board bcopy = copy(board);


  return moves;
}