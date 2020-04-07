#ifndef _MINIMAX_H_
#define _MINIMAX_H_

#include "board.h"
#include "checkalt.h"
#include "eval.h"
#include <algorithm>

// lets the AI choose a move
Board chooseMove(const Board& board, int difficulty = 1);

// minimax function for decision-making
double minimax(const Board& board, int depth, bool maxPlayer,
            double alpha, double beta);

#endif
