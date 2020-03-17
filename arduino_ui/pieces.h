#ifndef __PIECES_H
#define __PIECES_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#define B_SQ 35 // board square side length

// struct that stores piece information
struct Piece {
  uint8_t colour;
  bool king;
  uint8_t pos; // position of the piece from 0 to 31
};

// cursor position on the screen
struct drawPos {
  uint16_t x;
  uint16_t y;
};

void drawPiece(Piece piece);

#endif