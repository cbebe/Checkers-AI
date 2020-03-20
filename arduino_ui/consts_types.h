#ifndef _CONSTS_TYPES_H
#define _CONSTS_TYPES_H

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <SPI.h>
#include <SD.h>

#include "screenpos.h"

#define SD_CS 10

#define NUM_PIECES 12 // number of pieces per player
#define B_SQ 35 // board square side length

#define BOARD_DARK 19458 // colours for game board
#define BOARD_LIGHT 57113 // please change i don't like


typedef enum {NONE, BOTW, PLAYERW, DRAW} win;
typedef enum {NO_PIECE, PIECE, CHAIN, DONE} selected;
typedef enum {EMPTY, PLAYER, BOT} tile;

// struct that stores piece information
struct Piece {
  int8_t colour; // colour of the piece
  tile side; // 1 for player 2 for bot
  bool king;
  // position of the piece from 0 to 31
  // -1 means captured
  int8_t pos; 
};


struct sharedVars {
  
  MCUFRIEND_kbv* tft; // the tft display
  // array to store all pieces
  Piece gamePieces[NUM_PIECES * 2];
  // array to store all board positions
  tile board[32];
  
  int8_t selected; // current selected tile
};

#endif