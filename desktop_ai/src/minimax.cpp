#include "minimax.h"

static int nodes = 0;

// lets the AI choose a move based on minimax
Board chooseMove(const Board& board, int difficulty) {
  nodes = 0; // reset the number of children

  // get the possible moves the AI can make
  bList boardList = boardStates(board, true);

  // chance that the AI will make a random move
  // the higher the difficulty the lower the chance
  if (!(rand() % difficulty)) {
    // AI has chosen a random move
    return boardList[rand() % boardList.size()];
  }

  // now the AI will use minimax to find the best move
  
  int maxVal = -inf; // the AI is the maximizing player
  int depth = 4;
  Board bestBoard;

  for (auto bEval : boardList) {
    // get the evaluation of the move
    int eval = minimax(bEval, depth, true, -inf, inf);

    if (eval > maxVal) {
      // this is the new chosen board      
      bestBoard = bEval;
      maxVal = eval;
    }
  }
  bestBoard.display();
  // print board value
  std::cout << "Board value: " << maxVal << std::endl;
  std::cout << "Number of children: " << nodes << std::endl;
  
  return bestBoard;
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
      nodes++; // count the number of children
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
      nodes++; // count the number of children

      eval = minimax(child, depth - 1, alpha, beta, true);
      minEval = std::min(minEval, eval);

      // prune the other branches
      beta = std::min(beta, eval);
      if (beta <= alpha) {break;}
    }
    return minEval;
  }
}