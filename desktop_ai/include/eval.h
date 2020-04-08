#ifndef _EVAL_H_
#define _EVAL_H_

#include <array>
#include "piece.h"
#include "offset.h"
#include "board.h"

// pick an arbitrarily large number for "infinity"
const double inf = 1000000000000;

// consts for heuristics
const double defended = 5.5;
const double vulnerable = -100;

const double pawnVal = 4.5;
const double kingVal = 7.5;

const double backrow = 1.6;
const double midrow = 1.1;
const double midbox = 1.3;

namespace pos {
  const double b = backrow;
  const double d = midbox;
  const double r = midrow;

  const double values[] = {   b,    b,    b,    b,
                           1,    1,    1,    1,
                              1,    1,    1,    1,
                           r,    d,    d,    r,
                              r,    d,    d,    r,
                           1,    1,    1,    1,
                              1,    1,    1,    1,
                           b,    b,    b,    b};

}


// return piece value
double pieceValue(Piece pc);

// checks for endgame conditions
double gameOver(const Board& board);

// evaluates the board
double staticEval(const Board& board, bool player);

#endif