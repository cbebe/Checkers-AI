#include "minimax.h"

// lets the AI choose a move
Board chooseMove(const Board& board, int difficulty) {

  // while minimax is not yet implemented, let the AI
  // make completely random moves
  difficulty = 1;

  // chance that the AI will make a random move
  // the higher the difficulty the lower the chance
  if (!(rand() % difficulty)) {
    // get the possible moves the AI can make
    bList boardList = boardStates(board, true);
    // for now, just return random moves
    return boardList[rand() % boardList.size()];
  }
  // implement minimax here
  
  return board;
}

// recursive function to find the min/max value of a move
int minimax(const Board& board, int depth, bool maxPlayer, int alpha, int beta) {
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