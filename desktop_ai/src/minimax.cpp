#include "minimax.h"

// check for endgame condition
bool gameOver(int position) {

  return true;
}

// static evaluation of the board
// refer to the readme for the heuristics
int staticEval(int position) {

  return 0;
}

// not implemented yet
std::vector<int> children(int position) {
  std::vector<int> childList;
  return childList;
}

// recursive function to find the min/max value of a move
int minimax(int position, int depth, int alpha, int beta, bool maxPlayer) {
  if (depth == 0 || gameOver(position)) {
    return staticEval(position);
  }
  int eval;

  if (maxPlayer) {
    int maxEval = -inf;
    // not implemented yet
    for (auto child: children(position)) {

      eval = minimax(child, depth - 1, alpha, beta, false);
      maxEval = std::max(maxEval, eval);

      // prune the other branches
      alpha = std::max(alpha, eval);
      if (beta <= alpha) {break;}
    }
    return maxEval;
  } else {
    int minEval = inf;
    for (auto child: children(position)) {

      eval = minimax(child, depth - 1, alpha, beta, true);
      minEval = std::min(minEval, eval);

      // prune the other branches
      beta = std::min(beta, eval);
      if (beta <= alpha) {break;}
    }
    return minEval;
  }
}