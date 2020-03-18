#include "game_mechanics.h"


extern sharedVars shared;

/* int8_t touchPiece():
Determines which position of board that was touched
Returns -1 if the board is untouched
or a light tile was touched in the board
Returns -2 if out of bounds */

int8_t touchPiece() {
  screenPos tp = processTouchScreen();
  // if touch screen was untouched or out of bounds
  if (tp.x == UNTOUCHED){
    return -1;
  } 
  shared.tft->println(tp.x);
  shared.tft->println(tp.y);
  if ((tp.y > 300 || tp.y < 20) || (tp.x > 380 || tp.x < 100)) {
    return -2;
  }

  /* NOTE: The math here might be a bit hard to understand
  so just imagine the 8x8 board divided into 16 regions
  and those 16 regions each have a 2x2 matrix.
  The first two operations (fsRow and fsCol) determine which
  part of a matrix was touched. The second two then determine 
  which region in the 4x4 matrix. The position will then be 
  calculated in terms of these values.*/
 
  // remove board offset
  tp.x -= 100; tp.y -= 20;

  /* calculation for 2x2 matrix */

  // determine if first (0) or second (1) row was touched
  int8_t fsRow = (tp.y % (B_SQ * 2)) / B_SQ;
  // determine if first (0) or second (1) column was touched
  int8_t fsCol = (tp.x % (B_SQ * 2)) / B_SQ;

  /* calculation for 4x4 matrix */

  // determines which region of the board was touched
  int8_t regY = tp.y / (B_SQ * 2); 
  int8_t regX = tp.x / (B_SQ * 2); 

  // multiplication is logically the same as AND
  // addition is logically the same as OR
  if ((fsRow * fsCol) == 1 || 
      (fsRow + fsCol) == 0) {
    // a light tile was touched
    return -1;
  }
  
  return regX + (8 * regY) + (4 * fsRow);
}

void makeMove(int8_t piecePos) {

}

// lets player choose a piece to move
void choosePiece() {
  int8_t piecePos = touchPiece();
  while (piecePos != -2) {
    if (piecePos >= 0) {
      if (shared.board[piecePos] == PLAYER) {
        makeMove(piecePos);
      }
      shared.tft->println(piecePos);

    }
    delay(500);
    piecePos = touchPiece();
  }
  
  shared.tft->setCursor(0,0);
  shared.tft->fillRect(0,0,20,TFT_WIDTH, TFT_BLACK);
}