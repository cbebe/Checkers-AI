#include "piece.h"

extern sharedVars shared; 

/* int8_t nspiece::touch():
Determines which position of board that was touched
Returns -1 if the board is untouched
or a light tile was touched in the board  
Returns -2 if touch was out of bounds of the board */
int8_t nspiece::touch() {
  // namespace only used when not using would
  // lead to lesser readability
  using namespace c;
  screenPos tp = touch::process();
  // if touch screen was untouched
  if (tp.x == touch::untch){return -1;} 
  // if touch screen was out of bounds
  if ((tp.y > off_y + board_w || tp.y < off_y) || 
      (tp.x > off_x + board_w || tp.x < off_x)) {return -2;}

  /* NOTE: The math here might be a bit hard to understand
  so just imagine the 8x8 board divided into 16 regions
  and those 16 regions each have a 2x2 matrix.
  The first two operations (fsRow and fsCol) determine which
  part of a matrix was touched. The second two then determine 
  which region in the 4x4 matrix. The position will then be 
  calculated in terms of these values.*/
 
  // remove board offset
  tp.x -= off_x; tp.y -= off_y;
  /* calculation for 2x2 matrix */

  // determine if first (0) or second (1) row was touched
  int8_t fsRow = (tp.y % (board_sq * 2)) / board_sq;
  // determine if first (0) or second (1) column was touched
  int8_t fsCol = (tp.x % (board_sq * 2)) / board_sq;

  /* calculation for 4x4 matrix */

  // determines which region of the board was touched
  int8_t regY = tp.y / (board_sq * 2); 
  int8_t regX = tp.x / (board_sq * 2); 

  // multiplication is logically the same as AND
  // addition is logically the same as OR
  // checks if a light tile was touched
  if ((fsRow * fsCol) == 1 || 
      (fsRow + fsCol) == 0) {return -1;}
  
  return regX + (8 * regY) + (4 * fsRow);
}

// finds the piece in the gamePieces array
// returns a pointer to the piece
Piece* nspiece::find(int8_t pos) {
  return &shared.gamePieces[nspiece::index(pos)];
}

// remove a piece from the board
void nspiece::remove(int8_t piecePos) {
  // piece is captured
  nspiece::find(piecePos)->pos = -1;
  draw::clear(piecePos);
  shared.board[piecePos] = EMPTY;
}

// find a piece's index on the board array
// in terms of position
// return dummy piece if not found
int8_t nspiece::index(int8_t pos) {
  if (pos < 0) {return c::dummy;}
  // find the piece in the board that matches the position
  for (int i = 0; i < c::num_pieces * 2; i++) {
    if (shared.gamePieces[i].pos == pos) {return i;}
  }
  return c::dummy;
}