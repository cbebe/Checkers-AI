// ---------------
// checks.h
// ---------------
// Interface file for checks.cpp
//

#ifndef _CHECKS_H
#define _CHECKS_H

#include "consts_types.h"

// these functions alter the move struct/array
namespace check {
  // changes the move struct fields to MOVE
  // if there are valid moves
  void move(int8_t pos, move_st& moves);
  // changes the move struct fields to CAPTURE
  // if there are valid captures
  void capture(int8_t pos, move_st& moves);
  // removes backward moves if the pieces are not king
  void backwards(int8_t pos, move_st& moves);
}

// bool checks
namespace has {
  // if the struct has moves
  bool moves(const move_st& moves);
  // if the struct has captures
  bool captures(const move_st& moves);
}

#endif