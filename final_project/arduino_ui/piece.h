// ---------------
// piece.h
// ---------------
// Interface file for piece.cpp
//

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
  // remove a piece from the board
  void remove(int8_t piecePos);
}

#endif