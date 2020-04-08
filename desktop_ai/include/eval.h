#ifndef _EVAL_H_
#define _EVAL_H_

#include <array>
#include "piece.h"
#include "offset.h"
#include "board.h"

// pick an arbitrarily large number for "infinity"
const double inf = 10000000;

// consts for heuristics
const double defended = 3;
const double backrow = 4;
const double vulnerable = -3;
const double midrow = 1;
const double midbox = 3;
const double pawnVal = 4.5;
const double kingVal = 7.5;

// return piece value
double pieceValue(Piece pc);

// returns the piece's weight 
// depending on its position on the board
double positionValue(Piece pc, int8 index);

// checks for endgame conditions
double gameOver(const Board& board);

// evaluates the board
double staticEval(const Board& board);

#endif