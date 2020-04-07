#include "eval.h"

// returns a piece value
int pieceValue(Piece pc) {
  int pieceVal = 0; // assume empty at first
  if (pc != E) {
    if (pc == BK) {pieceVal = kingVal;}    
    else if (pc == B) {pieceVal = pawnVal;}    
    else if (pc == WK) {pieceVal = -kingVal;}    
    else if (pc == W) {pieceVal = -pawnVal;}
  }
  return pieceVal;
}

int positionValue(int8 index, std::array<Piece, bSize>& boardArray) {
  // if the conditions are not met,
  // the piece does not contribute to the decision making
  int posVal = 0; 
  Piece pc = boardArray[index];
  
  if (pc != E) {

  }
  return posVal;
}