#include "minimax.h"
#include "check.h"

// check for endgame condition
bool gameOver(const Board& board) {

  return true;
}

// return piece value
int pieceValue(const Board& board, int8 index) {
  int pieceVal = 0; // assume empty at first
  Piece pc = board.get(index);
  if (pc != E) {
    if (pc == BK) {pieceVal = 8;}    
    else if (pc == B) {pieceVal = 5;}    
    else if (pc == WK) {pieceVal = -8;}    
    else if (pc == W) {pieceVal = -5;}
  }
  return pieceVal;
}

// returns the piece's weight 
// depending on its position on the board
int positionValue(const Board& board, int8 index) {
  
}

// static evaluation of the board
// refer to the readme for the heuristics
int staticEval(const Board& board) {
  int eval = 0;
  for (int8 i = 0; i < bSize; i++) {
    int pcVal = pieceValue(board, i);
    int posVal = positionValue(board, i);
    eval += pcVal * posVal;
  }
  
  return 0;
}

void captureLeftAttempt(std::list<Board>& moves, const Board& board, int8 i){
  int leftEdge = 0;
  int rightEdge = 0;
  int bottomEdge = 0;

  if (i == 4 || i == 12 || i == 20 || i == 28){
    leftEdge = 1;
  }

  else if (i == 3 || i == 11 || i == 19 || i == 27){
    rightEdge = 1;
  }

  if (i >= 28 && i <= 31){
    bottomEdge = 1;
  }

  // Find left and right diagonal offset
  int8 leftOS = findLeftOS(i, leftEdge, bottomEdge);
  // Try and find capturable pieces: 

  // First check if a capture is possible: 

  if (leftOS != -1){ // If a left diagonal is available
    // Check if white piece is present: 

    if (pieceCheck(board, leftOS) == W || pieceCheck(board, leftOS) == WK){
      // Need to check if the white piece can be captured, where leftOS is its position

      // Cant be captured if its on left or bottom edge
      int whiteOnLeftEdge, whiteOnBottomEdge;
      if (leftOS == 4 || leftOS == 12 || leftOS == 20 || leftOS == 28){
        whiteOnLeftEdge = 1;
      }

      if (leftOS >= 28 && leftOS <= 31){
        whiteOnBottomEdge = 1;
      }
      

      if (whiteOnLeftEdge != 1 && whiteOnBottomEdge != 1){ // If not on edge, check if diagonal left OS is empty
        if (pieceCheck(board, findLeftOS(leftOS, 0, 0)) == E){
          // Success, piece is capturable!
          Board postMove = boardCopy(board);

          postMove.a[i] = E;
          postMove.a[leftOS] = E;
          
          postMove.a[findLeftOS(leftOS, 0, 0)] = B;

          moves.push_back(postMove);
        }
      }
    }
  }
}

Board captureRightAttempt(std::list<Board>& moves, const Board& board, int8 i){
  int leftEdge = 0;
  int rightEdge = 0;
  int bottomEdge = 0;

  if (i == 4 || i == 12 || i == 20 || i == 28){
    leftEdge = 1;
  }

  else if (i == 3 || i == 11 || i == 19 || i == 27){
    rightEdge = 1;
  }

  if (i >= 28 && i <= 31){
    bottomEdge = 1;
  }

  // Find left and right diagonal offset
  int8 rightOS = findRightOS(i, rightEdge, bottomEdge);

  // Try and find capturable pieces: 

  // First check if a capture is possible: 

  if (rightOS != -1){ // If a left diagonal is available
    // Check if white piece is present: 

    if (pieceCheck(board, rightOS) == W || pieceCheck(board, rightOS) == WK){
      // Need to check if the white piece can be captured, where leftOS is its position

      // Cant be captured if its on left or bottom edge
      int whiteOnRightEdge, whiteOnBottomEdge;
      if (i == 3 || i == 11 || i == 19 || i == 27){
        whiteOnRightEdge = 1;
      }

      if (leftOS >= 28 && leftOS <= 31){
        whiteOnBottomEdge = 1;
      }
      

      if (whiteOnRightEdge != 1 && whiteOnBottomEdge != 1){ // If not on edge, check if diagonal left OS is empty
        if (pieceCheck(board, findRightOS(rightOS, 0, 0)) == E){
          // Success, piece is capturable!
          Board postMove = boardCopy(board);

          postMove.a[i] = E;
          postMove.a[rightOS] = E;
          
          postMove.a[findRightOS(rightOS, 0, 0)] = B;

          moves.push_back(postMove);
        }
      }
    }
  } 
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
      captureLeftAttempt(moves, bcopy, i);
      captureRightAttempt(moves, bcopy, i);
      
    }

    else if (bcopy.get(i) == BK){ // If piece is black king

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