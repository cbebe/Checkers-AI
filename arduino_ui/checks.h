#ifndef _CHECKS_H
#define _CHECKS_H

#include "consts_types.h"

// these functions alter the move struct/array
namespace check {
  // changes the move struct fields to MOVE
  // if there are valid moves
  void move(const Piece& piece, moveSt& moves);
  // changes the move struct fields to CAPTURE
  // if there are valid captures
  void capture(const Piece& piece, moveSt& moves);
  // removes backward moves if the pieces are not king
  void backwards(const Piece& piece, moveSt& moves);
}

// bool checks
namespace has {
  // if the struct has moves
  bool moves(const moveSt& moves);
  // if the struct has captures
  bool captures(const moveSt& moves);
}

#endif