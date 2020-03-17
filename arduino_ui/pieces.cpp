#include "pieces.h"

extern MCUFRIEND_kbv tft;
extern Piece gamePieces[];

// determines cursor position on the screen
// given a piece's position on the board
drawPos piecePosition(uint8_t pos) {
  int8_t group = pos / 8; // position from 0 to 3
  int8_t ForS = (pos % 8) / 4; // first or second row of group
  int8_t col = pos % 4; // the column of the piece
  drawPos dp;
  dp.x = ((1 - ForS) * B_SQ) + (2 * col * B_SQ) + 117;
  dp.y = (2 * group * B_SQ) + (ForS * B_SQ) + 37;
  return dp;
}

// draw
void drawPiece(Piece piece) {
  drawPos dp = piecePosition(piece.pos);
  int colour = TFT_BLACK;
  if (piece.colour == 0 ) {
    colour = TFT_WHITE;
  }
  tft.fillCircle(dp.x, dp.y, 15, colour);

  // marks king piece
  if (piece.king) {
    tft.fillCircle(dp.x, dp.y, 4, TFT_RED);
  }
}

