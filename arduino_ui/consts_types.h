#ifndef _CONSTS_TYPES_H
#define _CONSTS_TYPES_H

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <SD.h>

#include "screenpos.h"
// defined constants
namespace c {
  const uint8_t sd_cs = 10; // sd card pin
  
  const uint8_t num_pieces = 12; // number of pieces per player
  const uint8_t dummy = 24;
  
  const uint8_t board_sq = 35; // board square side length
  const uint16_t board_w = board_sq * 8; // board width
  const uint16_t board_dark = 19458; // colours for game board
  const uint16_t board_light = 57113; // please change i don't like
  const uint8_t pc_rad = 15; // piece radius
  // board offsets
  const uint8_t off_x = 100;
  const uint8_t off_y = 20;
};

typedef enum {NONE, BOTW, PLAYERW, DRAW} win;
typedef enum {NO_PIECE, PIECE, CHAIN, DONE} selected;
typedef enum {EMPTY, PLAYER, BOT, OUT} tile;
// moves that can be made by a piece
typedef enum {NOT, MOVE, CAPTURE} move;


// struct that stores piece information
struct Piece {
  int8_t colour; // colour of the piece
  tile side; // 1 for player 2 for bot
  bool king;
  // position of the piece from 0 to 31
  // -1 means captured
  int8_t pos; 
};

// struct to store moves in all 4 directions
struct moveSt {
  move UL; move UR;
  move DL; move DR;
};

// struct that stores all shared variables
struct sharedVars {
  MCUFRIEND_kbv* tft; // the tft display
  // array to store all pieces + a dummy piece
  Piece gamePieces[c::num_pieces * 2 + 1];
  // array to store all board positions
  tile board[32];
  
  int8_t selected; // current selected tile
};

// returns the tile value of a board position
// use only for comparing, not for value assignment
tile board(int8_t pos);
// determines adjacent tile offset depending
// on which row the piece is in
void tileOS(int8_t p, int8_t *os);

#endif