#include "minimax.h"

static long long nodes;

// lets the AI choose a move based on minimax
Board chooseMove(const Board& board, int difficulty) {
  srand(time(NULL)); // time seed for rand function

  nodes = 0; // reset the number of children

  // get the possible moves the AI can make
  bList boardList = boardStates(board, true);

  // chance that the AI will make a random move
  // the higher the difficulty the lower the chance
  if (!(rand() % difficulty)) {
    std::cout << "RANDOM MOVE" << std::endl; 
    // AI has chosen a random move
    return boardList[rand() % boardList.size()];
  }

  // now the AI will use minimax to find the best move
  
  double maxVal = -inf; // the AI is the maximizing player
  int depth = 10;
  Board bestBoard;

  for (auto bEval : boardList) {
    // get the evaluation of the move
    double eval = minimax(bEval, depth, true, -inf, inf);

    if (eval > maxVal) {
      // this is the new chosen board      
      bestBoard = bEval;
      maxVal = eval;
    }
  }
  // print board value
  std::cout << "Board value: " << maxVal << std::endl;
  std::cout << "Number of children: " << nodes << std::endl;
  
  return bestBoard;
}

// checks for endgame conditions
bool gameOver(const Board& board) {
  int black = 0, white = 0;
  // counts the pieces on the board
  for (int i = 0; i < bSize; i++) {
    Piece pc = board.get(i);
    if (pc == B || pc == BK) {black++;}
    else if (pc == W || pc == WK) {white++;}
    if (black && white) {
      return false;
    }
  }
  // return true
  // if either side's pieces are all captured
  return true;
}

// recursive function to find the min/max value of a move
double minimax(const Board& board, int depth, bool maxPlayer, double alpha, double beta) {
  if (depth == 0) {
    return staticEval(board);
  } else if (gameOver(board)) {
    std::cout << "Someone won" << std::endl;
    // either side's pieces are all captured
    return staticEval(board); 
  }
  double eval;

  // get the possible moves that the player can make
  bList bStates = boardStates(board, maxPlayer);
  if (bStates.empty()) {
    std::cout << "Out of moves" << std::endl;
    return staticEval(board); // game has ended; no more moves
  }

  if (maxPlayer) {
    double maxEval = -inf;
    // make a tree of board states
    for (auto child: bStates) {
      nodes++; // count the number of children

      eval = minimax(child, depth - 1, false, alpha, beta);
      maxEval = std::max(maxEval, eval);

      // prune the other branches
      alpha = std::max(alpha, eval);
      if (beta <= alpha) {break;}
    }
    return maxEval;
  } else {
    double minEval = inf;
    // make a tree of board states
    for (auto child: bStates) {
      nodes++; // count the number of children

      eval = minimax(child, depth - 1, true, alpha, beta);
      minEval = std::min(minEval, eval);

      // prune the other branches
      beta = std::min(beta, eval);
      if (beta <= alpha) {break;}
    }
    return minEval;
  }
}