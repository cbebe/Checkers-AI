#ifndef _MOVE_H
#define _MOVE_H

#include "piece.h"

// namespace for move-related functions
namespace nsmove {
  // returns the legal move associated with a pair of position numbers
  move legal(int8_t pos, int8_t newPos, const moveSt& moves);
  // show valid moves
  void show(int8_t pos, const moveSt& moves);
  // checks if the piece can move and alters move struct to show moves
  bool canMove(int8_t piecePos, moveSt& moves, move type);
  // moves a piece
  void piece(int8_t oldPos, int8_t newPos);
  // captures a piece
  void capture(int8_t oldPos, int8_t newPos);
  // for capture chains
  void chain(int8_t pos);
}

#endif