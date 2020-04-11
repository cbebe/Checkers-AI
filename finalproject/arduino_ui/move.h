// ---------------
// move.h
// ---------------
// Interface file for move.cpp
//

#ifndef _MOVE_H
#define _MOVE_H

#include "piece.h"

// namespace for move-related functions
namespace nsmove {
  // returns the legal move associated with a pair of position numbers
  move legal(int8_t pos, int8_t newPos, const move_st& moves);
  // show valid moves
  void show(int8_t pos, const move_st& moves);
  // checks if the piece can move and alters move struct to show moves
  bool can_move(int8_t piecePos, move_st& moves, move type);
  // moves a piece
  void piece(int8_t oldPos, int8_t newPos);
  // captures a piece
  void capture(int8_t oldPos, int8_t newPos);
  // for capture chains
  void chain(int8_t pos);
}

#endif