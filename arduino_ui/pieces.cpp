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
    for (int8_t i = 0; i < 4; i++) {
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
  // namespace only used when not using would
  // lead to lesser readability
  using namespace c;
  screenPos tp = processTouchScreen();
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

// checks if the selected move is legal
bool legalMove(const Piece &piece, int8_t newPos, const moveSt& moves) {
  int8_t os[4];
  adjTileOS(piece.pos, os); // adjust adjacent tile offsets
  // CAPTUREs
  if (moves.UL == CAPTURE && newPos == piece.pos - 9) {return true;}
  if (moves.UR == CAPTURE && newPos == piece.pos - 7) {return true;}
  if (moves.DL == CAPTURE && newPos == piece.pos + 7) {return true;}
  if (moves.DR == CAPTURE && newPos == piece.pos + 9) {return true;}
  // MOVEs
  if (moves.UL == MOVE && newPos == piece.pos + os[0]) {return true;}
  if (moves.UR == MOVE && newPos == piece.pos + os[1]) {return true;}
  if (moves.DL == MOVE && newPos == piece.pos + os[2]) {return true;}
  if (moves.DR == MOVE && newPos == piece.pos + os[3]) {return true;}

  return false;
}

// lets player choose a piece to move
void choosePiece(selected& pieceSel, bool turn, moveSt& moves) {
  int8_t piecePos = touchPiece();
  // loop again if nothing was touched
  if (piecePos < 0) {return;} 

  // selecting a new piece
  tile currentPlayer = BOT;
  if (turn) {
    currentPlayer = PLAYER;
  }
  if (shared.board[piecePos] == currentPlayer) {
    if (pieceCanMove(piecePos, moves, currentPlayer)) {
      // do nothing if same piece was selected
      if (piecePos == shared.selected) {return;}
      // unhighlights old piece and its moves
      unhighlightPiece(shared.gamePieces[pieceIndex(shared.selected)]);
      shared.selected = piecePos;
      showMoves(piecePos, moves);
      pieceSel = PIECE; // now a piece is selected
    }
  } else if (shared.board[piecePos] == EMPTY) {
    if (pieceSel == NO_PIECE) {return;}
    if (pieceSel == PIECE) {
      // check if the moves are legal for this piece
      Piece* piece = &shared.gamePieces[pieceIndex(shared.selected)];
      if(legalMove(*piece, piecePos, moves)) {
        unhighlightPiece(*piece); // remove move marks
        movePiece(piece->pos, piecePos); // move piece
        shared.selected = -1; // now no piece is selected
        pieceSel = DONE; // done moving
      }
    }
  }
}

// determines cursor position on the screen
// given a piece's position on the board
screenPos piecePosition(int8_t pos) {
  int8_t group = pos / 8; // position from 0 to 3
  int8_t ForS = (pos % 8) / 4; // first or second row of group
  int8_t col = pos % 4; // the column of the piece
  screenPos dp;
  dp.x = (3/2 - ForS + 2 * col) * c::board_sq + c::off_x;
  dp.y = (2 * group + ForS + 1/2) * c::board_sq + c::off_y;
  return dp;
}

// clears the tile of a piece or move
void clearTile(int8_t tileNum) {
  if (tileNum > 0 && tileNum < 31) {
    screenPos dp = piecePosition(tileNum);
    // dp initially points to the centre of the square
    dp.x -= c::board_sq/2; dp.y -= c::board_sq/2;
    shared.tft->fillRect(dp.x, dp.y, c::board_sq, c::board_sq, c::board_dark);
  }
}

// draw piece on board
void drawPiece(const Piece& piece) {
  // does not draw if piece is captured
  if (piece.pos == -1) return;

  // find piece's position on screen
  screenPos dp = piecePosition(piece.pos);
  // colour scheme
  uint16_t colour[] = {TFT_BLACK, TFT_WHITE}; 
  // change colour for other side
  if (piece.colour == 0) {
    colour[0] = TFT_WHITE; colour[1] = TFT_BLACK;
  }

  shared.tft->fillCircle(dp.x, dp.y, c::pc_rad, colour[0]);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad - 3, colour[1]);

  // marks king piece
  if (piece.king) {
    shared.tft->fillCircle(dp.x, dp.y, c::pc_rad/4 + 1, TFT_RED);
  }
}

// highlight piece for moving
void highlightPiece(const Piece& piece) {
  // does not highlight if piece is captured
  if (piece.pos == -1) {return;}
  screenPos dp = piecePosition(piece.pos);
  // yellow ring on highlighted piece
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad, TFT_YELLOW);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad - 1, TFT_YELLOW);
}

// unhighlights selected piece
void unhighlightPiece(const Piece& piece) {
  if (piece.pos == -1) {return;}
  drawPiece(piece); // redraws piece to remove highlight
  int8_t os[4], dg[] = {-9, -7, 7, 9};
  adjTileOS(piece.pos, os); // adjusts adjacent tile offsets
  // clears the moves
  for (int i = 0; i < 4; i++) {
    if (shared.board[piece.pos + os[i]] == EMPTY) {
      clearTile(piece.pos + os[i]);
    }
    // clear capture moves
    if (shared.board[piece.pos + dg[i]] == EMPTY) {
      clearTile(piece.pos + dg[i]);
    }
  }
}

// find a piece's index on the board array
// in terms of position
// return dummy piece if not found
int8_t pieceIndex(int8_t pos) {
  if (pos < 0) {return c::dummy;}
  // find the piece in the board that matches the position
  for (int i = 0; i < c::num_pieces * 2; i++) {
    if (shared.gamePieces[i].pos == pos) {return i;}
  }
  return c::dummy;
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
