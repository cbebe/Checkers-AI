#include "checkalt.h"

//determines row offset for adjacent tiles
void rowOS(int8 pos, int8 *os) {
  using namespace std;
  if ((pos % 8) / 4) {
    copy(begin(os2), end(os2), os);
  } else {
    copy(begin(os1), end(os1), os);
  }
}

// copies the diagonal offsets to offset array
void diagOS(int8 *os) {
  std::copy(std::begin(dg), std::end(dg), os);
}

/* 
boolP boardCheck:
checks if tiles are empty/have enemies
neighbour is either adjacent or diagonal, 
for checking moves or jumps.
query is either empty or the enemy piece.
direction is either up or down, 
depending on which piece the side is on.
*/
boolP boardCheck(const Board& board, int8 pos, 
              tile_t neighbour, dir_t direction, Piece query) {
  int8 offset[4];
  // check which neighbour we're looking for
  if (neighbour == ADJACENT) {
    // adjacent offsets depend on piece's position
    rowOS(pos, offset); 
  } else {
    // diagonal offsets are constant in every direction
    diagOS(offset);
  }
  Piece queryK = E; // assume query is E
  if (query != E) {
    // assigning the query king piece
    queryK = (query == B) ? BK : WK;  
  }

  int8 i = (direction == UP) ? 0 : 2; // starting index for offset
  // get the pieces in the queried tiles
  Piece left = board.get(pos + offset[i]);
  Piece right = board.get(pos + offset[i + 1]);

  // check if the pieces match the query
  bool leftMove = left == query || left == queryK;
  bool rightMove = right == query || right == queryK;

  return {leftMove, rightMove};
}

moveP pieceMoves() {
  
}