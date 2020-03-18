#include "pieces.h"

extern sharedVars shared; 

// finds the piece from the board position
Piece findPiece(int8_t piecePos) {
  // return a dummy piece if not found (unlikely)
  Piece piece = {0, false, EMPTY, -1}; 
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

// draw piece on board
void drawPiece(Piece piece) {
  screenPos dp = piecePosition(piece.pos);
  uint16_t colour[] = {TFT_BLACK, TFT_WHITE}; 
  if (piece.colour == 0 ) {
    colour[0] = TFT_WHITE;
    colour[1] = TFT_BLACK;
  }
  shared.tft->fillCircle(dp.x, dp.y, 15, colour[0]);
  shared.tft->drawCircle(dp.x, dp.y, 12, colour[1]);


  // marks king piece
  if (piece.king) {
    shared.tft->fillCircle(dp.x, dp.y, 4, TFT_RED);
  }
}

// highlight piece for moving
void highlightPiece(Piece piece) {
  screenPos dp = piecePosition(piece.pos);
  shared.tft->drawCircle(dp.x, dp.y, 15, TFT_YELLOW);
  shared.tft->drawCircle(dp.x, dp.y, 14, TFT_YELLOW);
}