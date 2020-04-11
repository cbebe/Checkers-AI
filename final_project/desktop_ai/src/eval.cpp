#include "eval.h"

// returns a piece value
double pieceValue(Piece pc) {
  double pieceVal = 0; // assume empty at first
  if (pc != E) {
    if (pc == BK) {pieceVal = kingVal;}    
    else if (pc == B) {pieceVal = pawnVal;}    
    else if (pc == WK) {pieceVal = -kingVal;}    
    else if (pc == W) {pieceVal = -pawnVal;}
  }
  return pieceVal;
}

// checks for position value
double positionValue(Piece pc, int8 pos) {
  // if the conditions are not met,
  // the piece does not contribute to the decision making
  int8 row = pos/4; // get row number
  double posVal = 0;
  if (pc == B) {
    posVal = row;
  } else if (pc == W) {
    posVal = (7 - row);
  } else if (pc == WK || pc == BK) {
    // want the king to be in the centre
    posVal = abs(3.5 - row);  
  } 

  return posVal;
}

// checks for endgame conditions
// necessary so that the AI would 
// avoid losing as much as possible
double gameOver(const Board& board) {
  int black = 0, white = 0;
  // counts the pieces on the board
  for (int i = 0; i < bSize; i++) {
    Piece pc = board.get(i);
    if (pc == B || pc == BK) {black++;}
    else if (pc == W || pc == WK) {white++;}
    if (black && white) {
      return 0; // no one has lost yet
    }
  }
  if (!black) {
    // no more black pieces
    return -1;
  } 
  // no more white pieces
  return 1;
}

// performs a static evaluation on the board
// according to the given heuristics
double staticEval(const Board& board, bool player) {
  // check for endgame conditions first
  double eval = 0;
  // get board value if no one has lost yet
  double numpcs = 0;    
  for (int i = 0; i < bSize; i++) {
    Piece pc = board.get(i);
    if (pc != E) {numpcs++;} // counts number of pieces
  }
  for (int i = 0; i < bSize; i++) {
    Piece pc = board.get(i);
    double value = pieceValue(pc) * positionValue(pc, i);
    // mid/endgame is when there are less than half of the pieces left
    if (numpcs < 12) {
      // bring the kings to the centre
      if (pc == WK || pc == BK) {
        value *= pos::values[i];
      } else {
        // pawns will try harder to get kings
        value *= positionValue(pc, i);
      }
    } 
    eval += value;
    
  }
  eval /= numpcs; // normalizes the board value
  
  return eval;
}