// ---------------
// piece.cpp
// ---------------
// Contains all functions related to pieces on the board
//

#include "piece.h"

extern shared_vars shared; 

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
  if ((tp.y > off_y + b_width || tp.y < off_y) || 
      (tp.x > off_x + b_width || tp.x < off_x)) {return -2;}

  /* NOTE: The 8x8 board is divided into 16 regions
  and those 16 regions each have a 2x2 matrix.
  The first two operations (fsRow and fsCol) determine which
  part of a matrix was touched. The second two then determine 
  which region in the 4x4 matrix. The position will then be 
  calculated in terms of these values.*/
 
  // remove board offset
  tp.x -= off_x; tp.y -= off_y;
  /* calculation for 2x2 matrix */

  // determine if first (0) or second (1) row was touched
  int8_t fs_row = (tp.y % (b_sq * 2)) / b_sq;
  // determine if first (0) or second (1) column was touched
  int8_t fs_col = (tp.x % (b_sq * 2)) / b_sq;

  /* calculation for 4x4 matrix */

  // determines which region of the board was touched
  int8_t regY = tp.y / (b_sq * 2); 
  int8_t regX = tp.x / (b_sq * 2); 

  // multiplication is logically the same as AND
  // addition is logically the same as OR
  // checks if a light tile was touched
  if ((fs_row * fs_col) == 1 || 
      (fs_row + fs_col) == 0) {return -1;}
  
  return regX + (8 * regY) + (4 * fs_row);
}


// remove a piece from the board
void nspiece::remove(int8_t piecePos) {
  // piece is captured
  draw::clear(piecePos);
  shared.board[piecePos] = EMPTY;
}