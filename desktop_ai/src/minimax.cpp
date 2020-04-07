#include "minimax.h"





// recursive function to find the min/max value of a move
Board minimax(const Board& board, int depth, bool maxPlayer, int alpha, int beta) {
  if (depth == 0) {
    return staticEval(board);
  }
  int eval;

  if (maxPlayer) {
    int maxEval = -inf;
    bList bStates = boardStates(board, maxPlayer);
    if (bStates.empty()) {
      return staticEval(board); // game has ended; no more moves
    }
    // make a tree of board states
    for (auto child: bStates) {

      eval = minimax(child, depth - 1, alpha, beta, false);
      maxEval = std::max(maxEval, eval);

      // prune the other branches
      alpha = std::max(alpha, eval);
      if (beta <= alpha) {break;}
    }
    return maxEval;
  } else {
    int minEval = inf;
    bList bStates = boardStates(board, maxPlayer);
    if (bStates.empty()) {
      return staticEval(board); // game has ended; no more moves
    }

    // make a tree of board states
    for (auto child: bStates) {

      eval = minimax(child, depth - 1, alpha, beta, true);
      minEval = std::min(minEval, eval);

      // prune the other branches
      beta = std::min(beta, eval);
      if (beta <= alpha) {break;}
    }
    return minEval;
  }
}