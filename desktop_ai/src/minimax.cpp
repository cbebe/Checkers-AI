#include "minimax.h"

// check for endgame condition
bool gameOver(const Board& board) {

  return true;
}

// static evaluation of the board
// refer to the readme for the heuristics
int staticEval(const Board& board) {

  return 0;
}

// returns a list of possible board moves
// * TODO: on check.cpp, create functions that would check for possible moves
// * Without duplication of course
std::list<Board> possibleMoves(const Board& board, bool player) {
  std::list<Board> moves;
  Board bcopy = boardCopy(board);
  moves.push_back(bcopy);

  return moves;
}

// recursive function to find the min/max value of a move
int minimax(const Board& board, int depth, bool maxPlayer, int alpha, int beta) {
  if (depth == 0 || gameOver(board)) {
    return staticEval(board);
  }
  int eval;

  if (maxPlayer) {
    int maxEval = -inf;
    // not implemented yet
    for (auto child: possibleMoves(board, maxPlayer)) {

      eval = minimax(child, depth - 1, alpha, beta, false);
      maxEval = std::max(maxEval, eval);

      // prune the other branches
      alpha = std::max(alpha, eval);
      if (beta <= alpha) {break;}
    }
    return maxEval;
  } else {
    int minEval = inf;
    for (auto child: possibleMoves(board, maxPlayer)) {

      eval = minimax(child, depth - 1, alpha, beta, true);
      minEval = std::min(minEval, eval);

      // prune the other branches
      beta = std::min(beta, eval);
      if (beta <= alpha) {break;}
    }
    return minEval;
  }
}