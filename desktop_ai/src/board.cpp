#include "board.h"

// initializes a board with a given boart state string
Board::Board(const std::string& boardState) {
  boardArray = new Piece[bSize];
  // constructs board with given board state
  for (int i = 0; i < bSize; i++) {
    boardArray[i] = (Piece) (boardState[i] - '0');
  }
}

Board::~Board() {
  delete[] boardArray; // free allocated space
}

// returns the piece in the given position
Piece Board::get(int8 pos) const {
  // out of bounds of board
  if (pos < 0 || pos > 31) {return OUT;}
  // return piece in position
  return boardArray[pos];
}

// moves a piece from one position to another
// returns true if successful at moving
bool Board::move(int8 oldPos, int8 newPos) {
  Piece oldPc = get(oldPos);
  // no piece to move or no tile to move to
  if (oldPc == E || get(newPos) != E) return false;

  // moves piece from oldPos to newPos
  remove(oldPos); set(newPos, oldPc);
  return true;
}

// removes piece from the board
void Board::remove(int8 pos) {
  set(pos, E); // sets to empty
}

// displays board on stdout
void Board::display() const {
  using std::cout;
  using std::endl;

  cout << "  =================================================" << endl;
  cout << "   _______________________________________________" << endl;
  for (int i = 0; i <= 24; i += 8) 
  {
    cout << "  |     |     |     |     |     |     |     |     |" << endl;
    cout << "  |     |  "<< boardArray[i] << "  |     |  " << 
                            boardArray[i + 1] << "  |     |  " << 
                            boardArray[i + 2] << "  |     |  " <<
                            boardArray[i + 3] << "  |" << endl;
    cout << "  |_____|_____|_____|_____|_____|_____|_____|_____|" << endl;
    cout << "  |     |     |     |     |     |     |     |     |" << endl;
    cout << "  |  " << boardArray[i + 4] << "  |     |  " << 
                      boardArray[i + 5] << "  |     |  " << 
                      boardArray[i + 6] << "  |     |  " << 
                      boardArray[i + 7] << "  |     |  " << endl;
    cout << "  |_____|_____|_____|_____|_____|_____|_____|_____|" << endl;
  }
  cout << endl;
  cout << "  =================================================" << endl;
}

// returns a string of the current board state
std::string Board::stateString() const {
  std::string state;
  for (int i = 0; i < bSize; i++) {
    // casting enum to char
    state += ((char) boardArray[i]) + '0';
  }
  return state;
}

void Board::set(int8 pos, Piece pc) {
  // only set piece if within bounds
  if (pos >= 0 && pos < bSize) {
    boardArray[pos] = pc;
  }
}