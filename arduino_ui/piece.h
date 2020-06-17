// ---------------
// piece.h
// ---------------
// Interface file for piece.cpp
//

#ifndef __PIECE_H
#define __PIECE_H

#include "consts_types.h"
#include "shared.h"
#include "Touch.h"
#include "Draw.h"

// namespace for piece-related functions
namespace nspiece
{
  // returns the position of the touched tile
  int8_t touch();
  // remove a piece from the board
  void remove(int8_t piecePos);
} // namespace nspiece

#endif