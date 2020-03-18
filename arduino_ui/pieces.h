#ifndef __PIECES_H
#define __PIECES_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include "consts_types.h"

// cursor position on the screen
struct drawPos {
  uint16_t x;
  uint16_t y;
};

void drawPiece(Piece piece);

#endif