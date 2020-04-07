#include "check.h"

void captureLeftAttempt(std::list<Board>& moves, const Board& board, int8 i){
  int leftEdge = 0;
  int bottomEdge = 0;

  if (i == 4 || i == 12 || i == 20 || i == 28){
    leftEdge = 1;
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

    if (board.get(leftOS) == W || board.get(leftOS) == WK){
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
        if (board.get(findLeftOS(leftOS, 0, 0)) == E){
          // Success, piece is capturable!
          Board postMove = Board(board.stateString());

          postMove.move(i, findLeftOS(leftOS, 0, 0));
          postMove.remove(leftOS);
          moves.push_back(postMove);
        }
      }
    }
  }
}

void captureRightAttempt(std::list<Board>& moves, const Board& board, int8 i){
  int rightEdge = 0;
  int bottomEdge = 0;

  if (i == 3 || i == 11 || i == 19 || i == 27){
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
    Piece pc = board.get(rightOS);
    if (pc == W || pc == WK){
      // Need to check if the white piece can be captured, where leftOS is its position

      // Cant be captured if its on left or bottom edge
      int whiteOnRightEdge, whiteOnBottomEdge;
      if (i == 3 || i == 11 || i == 19 || i == 27){
        whiteOnRightEdge = 1;
      }

      if (rightOS >= 28 && rightOS <= 31){
        whiteOnBottomEdge = 1;
      }
      

      if (whiteOnRightEdge != 1 && whiteOnBottomEdge != 1){ // If not on edge, check if diagonal left OS is empty
        if (board.get(findRightOS(rightOS, 0, 0)) == E){
          // Success, piece is capturable!
          Board postMove = Board(board.stateString());

          postMove.move(i, findRightOS(rightOS, 0, 0));
          postMove.remove(rightOS);          

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

  int flag = 0; // Keps track of captures

  for (int8 i = 0; i < 32; i++){ // Iterate through all pieces
    if (board.get(i) == B){ // If piece is black
      // Check for capturable white piece in front
      captureLeftAttempt(moves, board, i);
      captureRightAttempt(moves, board, i);
      
    }

    else if (board.get(i) == BK){ // If piece is black king

    }
  }

  return moves;
}