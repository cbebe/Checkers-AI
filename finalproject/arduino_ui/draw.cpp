// ---------------
// draw.cpp
// ---------------
// Contains all functions related to printing of the TFT screen
//


#include "draw.h"

extern shared_vars shared;

// clears the tile of a piece or move
void draw::clear(int8_t tile) {
  if (tile >= 0 && tile <= 31) {
    screenPos dp = draw::position(tile);
    // dp initially points to the centre of the square
    dp.x -= c::b_sq/2; dp.y -= c::b_sq/2;
    shared.tft->fillRect(dp.x, dp.y, c::b_sq, c::b_sq, c::b_dark);
  }
}

// draw piece on board
void draw::piece(int8_t pos) {
  // does not draw if piece is not in the board
  if (pos < 0 || pos > 31) return;
  Piece p = board(pos);
  if (p == EMPTY) return; // no piece, return

  // find piece's position on screen
  screenPos dp = draw::position(pos);
  // colour scheme
  uint16_t colour[] = {TFT_WHITE, TFT_BLACK}; 
  // change colour for bots
  if (p == BOT || p == BK) {
    colour[0] = TFT_BLACK; colour[1] = TFT_WHITE;
  }
  shared.tft->fillCircle(dp.x, dp.y, c::pc_rad, colour[0]);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad - 3, colour[1]);

  // marks king piece
  if (p == PK || p == BK) {
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
  dp.x = (1 - ForS + 2 * col) * c::b_sq + c::b_sq/2 + c::off_x;
  dp.y = (2 * group + ForS ) * c::b_sq + c::b_sq/2 + c::off_y;
  return dp;
}

// highlight piece for moving/capturing
void draw::highlight(int8_t pos, bool cap) {
  // does not highlight if piece is out of bounds
  if (pos >= 0 && pos < 32) {
    screenPos dp = draw::position(pos);
    
    int16_t colour = cap ? TFT_RED : TFT_YELLOW;
    // yellow ring on highlighted piece if moving
    // red ring on highlighted piece if capturing
    shared.tft->drawCircle(dp.x, dp.y, c::pc_rad, colour);
    shared.tft->drawCircle(dp.x, dp.y, c::pc_rad - 1, colour);
  }
}

// unhighlights selected piece
void draw::unhighlight(int8_t pos) {
  if (pos < 0 || pos > 31) return;

  draw::piece(pos); // redraws piece to remove highlight
  int8_t os[4];
  tileOS(pos, os); // adjusts adjacent tile offsets
  // clears the moves
  for (int i = 0; i < 4; i++) {
    if (board(pos + os[i]) == EMPTY) {
      draw::clear(pos + os[i]);
    }
    // clear capture moves
    if (board(pos + c::dg[i]) == EMPTY) {
      draw::clear(pos + c::dg[i]);
    }
  }
}

// marks the moves on the board
void draw::mark(int8_t pos) {
  screenPos dp = draw::position(pos);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad/2, TFT_RED);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad/2 + 1, TFT_RED);
}