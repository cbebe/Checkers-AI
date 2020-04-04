#include "check.h"

//determines row offset for adjacent tiles
void rowOS(int8 pos, int8 *os) {
  using namespace std;
  if ((pos % 8) / 4) {
    copy(begin(os2), end(os2), os);
  } else {
    copy(begin(os1), end(os1), os);
  }
}

// copies the diagonal offsets to
void diagOS(int8 *os) {
  std::copy(std::begin(dg), std::end(dg), os);
}


int findLeftOS(int pos, int leftEdge, int bottomEdge) {
  if (!(leftEdge == 1 || bottomEdge == 1)){
    // Left offset position only exists if piece is not at left or bottom edge
    if ((pos % 8)/ 4){
      return pos+3;
    }
    else{
      return pos+4;
    }
  }

  else{
    return 0; // If left or bottom edge, return 0
  }
}

int findRightOS(int pos, int rightEdge, int bottomEdge){
  if (!(rightEdge == 1 || bottomEdge == 1)){
    // right offset position only exists if piece is not at left or bottom edge
    if ((pos % 8)/ 4){
      return pos+4;
    }
    else{
      return pos+5;      
    }
  }

  else{
    return 0; // If right or bottom edge, return 0
  }
}


/* bp boardCheck:
checks if tiles are empty/have enemies
nbr is either adjacent or diagonal, 
for checking moves or jumps.
q is either empty or the enemy piece.
dir_t d is either up or down, 
depending on which piece the side is on.
*/
bp boardCheck(const Board& board, int8 pos, 
              tile_t nbr, dir_t d, Piece q) {
  int8 os[4];
  if (nbr == ADJACENT) {
    rowOS(pos, os);
  } else {
    diagOS(os);
  }

  int8 i = (d == UP) ? 0 : 2; // starting index for offset
  bp lr(board.get(pos + os[i]) == q, 
        board.get(pos + os[i + 1]) == q);
  return lr;
}

std::list<mp> pieceMoves(const Board& board, int8 piecePos) {
  std::list<mp> kek;
  // pls help
  return kek;
} 