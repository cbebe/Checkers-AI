#ifndef _EVAL_H_
#define _EVAL_H_

#include <array>
#include "piece.h"
#include "board.h"

// max value for 32-bit signed
const int inf = 2147483647;

// consts for heuristics
const int defended = 3;
const int backrow = 4;
const int vulnerable = -3;
const int midrow = 1;
const int midbox = 3;
const int pawnVal = 5;
const int kingVal = 8;

// return piece value
int pieceValue(Piece pc);

// returns the piece's weight 
// depending on its position on the board
int positionValue(Piece pc, int8 index);

// evaluates the board
int staticEval(const Board& board);

#endif