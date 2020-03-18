#ifndef _CONSTS_TYPES_H
#define _CONSTS_TYPES_H

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS 10
#define TFT_HEIGHT 320
#define TFT_WIDTH 480
#define NUM_PIECES 12 // number of pieces per player
#define B_SQ 35 // board square side length

// struct that stores piece information
struct Piece {
  uint8_t colour; // colour of the piece
  bool king;
  // position of the piece from 0 to 31
  // -1 means captured
  int8_t pos; 
};

// cursor position on the screen
struct screenPos {
  int16_t x;
  int16_t y;
};

struct shared_vars {
  // the tft display
  MCUFRIEND_kbv* tft;
  // array to store all pieces
  Piece gamePieces[NUM_PIECES * 2];

};

#endif