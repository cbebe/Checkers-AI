#ifndef _MINIMAX_H_
#define _MINIMAX_H_

#include "board.h"
#include "check.h"
#include <algorithm>

// max value for 32-bit signed
const int inf = 2147483647;

// minimax function for decision-making
int minimax(const Board& board, int depth, bool maxPlayer,
            int alpha = -inf, int beta = inf);

#endif
