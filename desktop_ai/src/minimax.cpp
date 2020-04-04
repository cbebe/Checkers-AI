#include "minimax.h"
#include "check.h"

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

  int flag = 0; // Keps track of captures

  for (int8 i = 0; i < 32; i++){ // Iterate through all pieces
    if (pieceCheck(bcopy, i) == B){ // If piece is black
      // Check for capturable white piece in front

      // Check if its an edge piece

      int leftEdge = 0;
      int rightEdge = 0;
      int bottomEdge = 0;

      if (i == 4 || i == 12 || i == 20 || i == 28){
        leftEdge == 1;
      }

      else if (i == 3 || i == 11 || i == 19 || i == 27){
        rightEdge == 1;
      }

      else if (i >= 28 && i <= 31){
        bottomEdge == 1;
      }

      // Find left and right diagonal offset
      int leftOS = findLeftOS(i, leftEdge, bottomEdge);
      int rightOS = findRightOS(i, rightEdge, bottomEdge);

      // Try and find capturable pieces: 

      // First check if a capture is possible: 

      if (leftOS != 0){ // If a left diagonal is available
        
      }
    }

    else if (pieceCheck(bcopy, i) == BK){ // If piece is black king

    }
  }

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