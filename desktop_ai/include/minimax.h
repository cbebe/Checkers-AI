#ifndef _MINIMAX_H_
#define _MINIMAX_H_

#include "board.h"
#include "checkalt.h"
#include <algorithm>

// minimax function for decision-making
Board minimax(const Board& board, int depth, bool maxPlayer,
            int alpha = -inf, int beta = inf);

#endif
