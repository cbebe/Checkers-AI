#ifndef _SHARED_H
#define _SHARED_H

#include "consts_types.h"

// struct that stores all shared variables
struct shared_vars
{
  MCUFRIEND_kbv *tft;     // the tft display
  Piece board[c::b_size]; // array to store all board positions
  int8_t currentPc;       // current selected piece
};

// returns the tile value of a board position
// use only for comparing, not for value assignment
Piece board(int8_t pos);
// determines adjacent tile offset depending
// on which row the piece is in
void tileOS(int8_t p, int8_t *os);
// for print debugging
void db(const char *msg);

#endif