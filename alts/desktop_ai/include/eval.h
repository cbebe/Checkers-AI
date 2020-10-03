#ifndef _EVAL_H_
#define _EVAL_H_

#include <array>
#include "piece.h"
#include "offset.h"
#include "board.h"

// pick an arbitrarily large number for "infinity"
const double inf = 1000000000000;

// consts for heuristics
const double pawnVal = 5;
const double kingVal = 9;

namespace pos
{
   const double b = 0.5;
   const double d = 2;
   const double r = 1.5;
   // weights for each position in the board
   const double values[] = {b, b, b, b,
                            1, 1, 1, 1,
                            1, r, r, 1,
                            r, d, d, r,
                            r, d, d, r,
                            1, r, r, 1,
                            1, 1, 1, 1,
                            b, b, b, b};
} // namespace pos

// return piece value
double pieceValue(Piece pc);

// checks for endgame conditions
double gameOver(const Board &board);

// evaluates the board
double staticEval(const Board &board, bool player);

#endif