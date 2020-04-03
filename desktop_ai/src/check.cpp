#include "check.h"

// determines row offset for adjacent tiles
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
  bp lr(board.a[pos + os[i]] == q, 
        board.a[pos + os[i + 1]] == q);
  return lr;
}


std::list<mp> pieceMoves(const Board& board, int8 piecePos) {
  std::list<mp> kek;
  // pls help
  return kek;
} 