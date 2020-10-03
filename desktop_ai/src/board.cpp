#include "board.h"

// initializes a board with a given board state string
Board::Board(const std::string& boardState) {
  // constructs board with given board state
  for (int i = 0; i < bSize; i++) {
    // cast number char to Piece enum
    boardArray[i] = static_cast<Piece>(boardState[i] - '0');
  }
}

// returns the piece in the given position
Piece Board::get(int8 pos) const {
  // out of bounds of board
  if (pos < 0 || pos >= bSize) {return OUT;}
  // return piece in position
  return boardArray[pos];
}

// set a board position to a given Piece type
void Board::set(int8 pos, Piece pc) {
  // only set piece if within bounds
  if (pos >= 0 && pos < bSize) {
    boardArray[pos] = pc;
  }
}

// moves a piece from one position to another
// returns true if successful at moving
bool Board::move(int8 oldPos, int8 newPos) {
  Piece pc = get(oldPos);
  // no piece to move or no tile to move to
  if (pc == E || get(newPos) != E) return false;

  // checks for promotion
  if (pc == W || pc == B) {
    if (pc == B && newPos > 27) {
      pc = BK; // promote to king
    } else if (pc == W && newPos < 4) {
      pc = WK; // promote to king
    }
  }

  // moves piece from oldPos to newPos
  remove(oldPos); set(newPos, pc);
  return true;
}

// removes piece from the board
void Board::remove(int8 pos) {
  set(pos, E); // sets to empty
}

// prints the board to stdout 
void Board::display() const {
  using std::cout;
  cout << "  =================================================\n";
  cout << "   _______________________________________________\n";
  for (int i = 0; i < 4; i++)  {
    cout << "  |     |     |     |     |     |     |     |     |\n";
    for (int j = i * 8; j < (i * 8) + 4; j++) {
      cout << "  |     |  "<< boardArray[j]; 
    }
    cout << "  |\n  |_____|_____|_____|_____|_____|_____|_____|_____|\n";
    cout << "  |     |     |     |     |     |     |     |     |\n  |  ";
    for (int j = i * 8; j < (i* 8) + 4; j++) {
      cout << boardArray[j + 4] << "  |     |  "; 
    }
    cout << "\n  |_____|_____|_____|_____|_____|_____|_____|_____|\n";
  }
  cout << "  =================================================\n";
}

// returns a string representation of the current board state
std::string Board::stateString() const {
  std::string state;
  for (int i = 0; i < bSize; i++) {
    // casting enum to char
    state += static_cast<char>(boardArray[i]) + '0';
  }
  return state;
}