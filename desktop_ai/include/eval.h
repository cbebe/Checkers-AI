#ifndef _EVAL_H_
#define _EVAL_H_

#include <array>

// max value for 32-bit signed
const int inf = 2147483647;

const int defended = 3;
const int backrow = 4;
const int vulnerable = -3;
const int midrow = 1;
const int midbox = 3;
const int pawnVal = 5;
const int kingVal = 8;
const int8 bSize = 32; // board size

typedef signed char int8;
typedef enum pc {
  E, // empty
  W,B, // white and black
  WK,BK, // white and black kings
  OUT // out of bounds
} Piece;


// return piece value
int pieceValue(const Board& board, int8 index);


// returns the piece's weight 
// depending on its position on the board
int positionValue(const Board& board, int8 index) {
  // if the conditions are not met,
  // the piece does not contribute to the decision making
  int posVal = 0; 
  Piece pc = board.get(index);
  
  if (pc != E) {

  }
  return posVal;
}

// static evaluation of the board
// refer to the readme for the heuristics
int staticEval(const Board& board) {
  int eval = 0;
  for (int8 i = 0; i < bSize; i++) {
    int pcVal = pieceValue(board, i);
    int posVal = positionValue(board, i);
    eval += pcVal * posVal;
  }
  
  return 0;
}

#endif