#include "pieces.h"

extern sharedVars shared; 

// determines adjacent tile offset depending
// on which row the piece is in
void adjTileOS(int8_t p, int8_t *os) {
  // tile offsets {0:UL, 1:UR, 2:DL, 3:DR}
  os[0] = -4; os[2] = 4;
  os[1] = -3; os[3] = 5; 
  // second row has different offsets
  if (((p % 8)/ 4)) {
    for (int i = 0; i < 4; i++) {
      os[i] -= 1;
    } 
  }
}

/* int8_t touchPiece():
Determines which position of board that was touched
Returns -1 if the board is untouched
or a light tile was touched in the board  
Returns -2 if touch was out of bounds of the board */
int8_t touchPiece() {
  screenPos tp = processTouchScreen();
  // if touch screen was untouched
  if (tp.x == UNTOUCHED){
    return -1;
  } 
  // if touch screen was out of bounds
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

// lets player choose a piece to move
void choosePiece(selected& pieceSel) {
  int8_t piecePos = touchPiece();
  // loop again if nothing was touched
  if (piecePos == -1) {return;} 

  if (shared.board[piecePos] == EMPTY) {
    if (pieceSel == NO_PIECE) {return;}
    if (pieceSel == PIECE) {
      Piece piece = findPiece(shared.selected);
      unhighlightPiece(piece);
      movePiece(piece.pos, piecePos);
      pieceSel = DONE;
      return;
    }
  }
  // selecting a new piece
  moveSt moves;
  if (pieceCanMove(piecePos, moves)) {
    if (piecePos == shared.selected) {return;}
    shared.tft->println("hey");
    pieceSel = PIECE;
    Piece oldPiece = findPiece(shared.selected);
    unhighlightPiece(oldPiece);
    shared.selected = piecePos;
    showMoves(piecePos, moves);
    return;
  }
}

// finds the piece from the board position
Piece findPiece(int8_t piecePos) {
  // return a dummy piece if not found (unlikely)
  Piece piece = {0, EMPTY, false, -1}; 
  for (int i = 0; i < 2 * NUM_PIECES; i++) {
    if (shared.gamePieces[i].pos == piecePos) {
      piece = shared.gamePieces[i];
      break;
    }
  }
  return piece;
}

// determines cursor position on the screen
// given a piece's position on the board
screenPos piecePosition(int8_t pos) {
  int8_t group = pos / 8; // position from 0 to 3
  int8_t ForS = (pos % 8) / 4; // first or second row of group
  int8_t col = pos % 4; // the column of the piece
  screenPos dp;
  dp.x = ((1 - ForS) * B_SQ) + (2 * col * B_SQ) + 117;
  dp.y = (2 * group * B_SQ) + (ForS * B_SQ) + 37;
  return dp;
}

// clears the tile of a piece or move
void clearTile(int8_t tileNum) {
  if (tileNum < 0 || tileNum > 31) {return;}
  screenPos dp = piecePosition(tileNum);
  dp.x -= B_SQ/2; dp.y -= B_SQ/2;
  shared.tft->fillRect(dp.x, dp.y, B_SQ, B_SQ, BOARD_DARK);
}

// draw piece on board
void drawPiece(Piece& piece) {
  // does not draw if piece is captured
  if (piece.pos == -1) return;

  // find piece's position on screen
  screenPos dp = piecePosition(piece.pos);
  // colour scheme
  uint16_t colour[] = {TFT_BLACK, TFT_WHITE}; 
  // change colour for other side
  if (piece.colour == 0) {
    colour[0] = TFT_WHITE;
    colour[1] = TFT_BLACK;
  }

  shared.tft->fillCircle(dp.x, dp.y, PC_RAD, colour[0]);
  shared.tft->drawCircle(dp.x, dp.y, PC_RAD - 3, colour[1]);

  // marks king piece
  if (piece.king) {
    shared.tft->fillCircle(dp.x, dp.y, 4, TFT_RED);
  }
}

// highlight piece for moving
void highlightPiece(Piece& piece) {
  // does not highlight if piece is captured
  if (piece.pos == -1) return;
  screenPos dp = piecePosition(piece.pos);
  // yellow ring on highlighted piece
  shared.tft->drawCircle(dp.x, dp.y, PC_RAD, TFT_YELLOW);
  shared.tft->drawCircle(dp.x, dp.y, PC_RAD - 1, TFT_YELLOW);
}

// unhighlights selected piece
void unhighlightPiece(Piece& piece) {
  drawPiece(piece);
  int8_t os[4];
  adjTileOS(piece.pos, os);
  for (int i = 0; i < 4; i++) {
    if (shared.board[piece.pos + os[i]] == EMPTY) {
      clearTile(piece.pos + os[i]);
    }
  }
}

// find a piece's index on the board array
// in terms of position
int8_t pieceIndex(int8_t pos) {
  if (pos < 0) {return -1;}
  // find the piece in the board that matches the position
  for (int i = 0; i < NUM_PIECES * 2; i++) {
    if (shared.gamePieces[i].pos == pos) {
      return i;
    }
  }
  return -1;
}



// moves a piece from one position to another
void movePiece(int8_t oldPos, int8_t newPos) {
  int8_t pi = pieceIndex(oldPos);
  // update piece's position in the board
  shared.gamePieces[pi].pos = newPos;
  // now tile is empty
  clearTile(oldPos);
  // draw piece in new position
  drawPiece(shared.gamePieces[pi]);
  // update board
  shared.board[oldPos] = EMPTY;
  shared.board[newPos] = shared.gamePieces[pi].side;
}

void testing(int8_t &state) {
  // int8_t pos = touchPiece();

  // if (pos > 0 && pos != shared.selected) {
  //   if (state == 0) {
  //     shared.selected = pos;
  //     state = 1;
  //   } else if (state == 1) {
  //     movePiece(shared.selected, pos);
  //     shared.tft->println("moved");
  //     state = 0;
  //   }
  //   delay(500);
  // }
}