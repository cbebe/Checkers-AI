#include "draw.h"

extern sharedVars shared;

// clears the tile of a piece or move
void draw::clear(int8_t tileNum) {
  if (tileNum >= 0 && tileNum <= 31) {
    screenPos dp = draw::position(tileNum);
    // dp initially points to the centre of the square
    dp.x -= c::board_sq/2; dp.y -= c::board_sq/2;
    shared.tft->fillRect(dp.x, dp.y, c::board_sq, c::board_sq, c::board_dark);
  }
}

// draw piece on board
void draw::piece(const Piece& piece) {
  // does not draw if piece is captured
  if (piece.pos == -1) return;

  // find piece's position on screen
  screenPos dp = draw::position(piece.pos);
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

// determines cursor position on the screen
// given a piece's position on the board
screenPos draw::position(int8_t pos) {
  int8_t group = pos / 8; // position from 0 to 3
  int8_t ForS = (pos % 8) / 4; // first or second row of group
  int8_t col = pos % 4; // the column of the piece
  screenPos dp;
  dp.x = (1 - ForS + 2 * col) * c::board_sq + c::board_sq/2 + c::off_x;
  dp.y = (2 * group + ForS ) * c::board_sq + c::board_sq/2 + c::off_y;
  return dp;
}

// highlight piece for moving/capturing
void draw::highlight(const Piece& piece, bool cap) {
  // does not highlight if piece is captured
  if (piece.pos == -1) {return;}
  screenPos dp = draw::position(piece.pos);
  
  int16_t colour = cap ? TFT_RED : TFT_YELLOW;
  // yellow ring on highlighted piece if moving
  // red ring on highlighted piece if capturing
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad, colour);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad - 1, colour);
}

// unhighlights selected piece
void draw::unhighlight(const Piece& piece) {
  if (piece.pos == -1) {return;}
  draw::piece(piece); // redraws piece to remove highlight
  int8_t os[4], dg[] = {-9, -7, 7, 9};
  tileOS(piece.pos, os); // adjusts adjacent tile offsets
  // clears the moves
  for (int i = 0; i < 4; i++) {
    if (board(piece.pos + os[i]) == EMPTY) {
      draw::clear(piece.pos + os[i]);
    }
    // clear capture moves
    if (board(piece.pos + dg[i]) == EMPTY) {
      draw::clear(piece.pos + dg[i]);
    }
  }
}

// marks the moves on the board
void draw::mark(int8_t pos) {
  screenPos dp = draw::position(pos);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad/2, TFT_RED);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad/2 + 1, TFT_RED);
}