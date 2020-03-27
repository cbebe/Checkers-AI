#ifndef __PIECE_H
#define __PIECE_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include "consts_types.h"

#include "touchs.h"
#include "draw.h"
#include "checks.h"

// namespace for piece-related functions
namespace nspiece {
  // returns the position of the touched tile
  int8_t touch();
  // find the piece given the position
  Piece* find(int8_t pos);
  // give the index of the piece in the game piece array
  int8_t index(int8_t pos);
  // remove a piece from the board
  void remove(int8_t piecePos);
}

#endif