#ifndef _CONSTS_TYPES_H
#define _CONSTS_TYPES_H

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <SD.h>

#include "screenpos.h"

typedef enum {NONE, BOTW, PLAYERW, DRAW} win;
typedef enum {NO_PIECE, PIECE, DONE} selected;
typedef enum {EMPTY, BOT, PLAYER, BK, PK, OUT} piece_t;
// moves that can be made by a piece
typedef enum {NOT, MOVE, CAPTURE} move;

// struct to store moves in all 4 directions
struct move_st {
  move m[4]; // wrap move array in a struct 
};

// defined constants
namespace c {
  const uint8_t sd_cs = 10; // sd card pin
  
  const uint8_t num_pcs = 12; // pieces per player 
  const uint8_t b_size = 32; // board array size
  
  const uint8_t b_sq = 35; // board square side length
  const uint16_t b_width = b_sq * 8; // board width

  const uint16_t b_dark = 19458; // colours for game board
  const uint16_t b_light = 57113; // please change i don't like
  
  const uint8_t pc_rad = 15; // piece radius
  // board offsets
  const uint8_t off_x = 100;
  const uint8_t off_y = 20;
  // diagonal moves are constant
  const int8_t dg[] = {-9, -7, 7, 9};
  // empty move array
  const move_st empty_m = {{NOT, NOT, NOT, NOT}};

  const uint16_t t10s = 10000; // 10 second timeout
  const uint16_t t20s = 20000; // 20 second timeout
};

// struct that stores all shared variables
struct shared_vars {
  MCUFRIEND_kbv* tft; // the tft display
  // array to store all board positions
  piece_t board[c::b_size];
  int8_t selected; // current selected piece
};

// returns the tile value of a board position
// use only for comparing, not for value assignment
piece_t board(int8_t pos);
// determines adjacent tile offset depending
// on which row the piece is in
void tileOS(int8_t p, int8_t *os);
// for print debugging
void db(const char* msg);

#endif