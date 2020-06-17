// ---------------
// checks.h
// ---------------
// Interface file for checks.cpp
//

#ifndef _CHECKS_H
#define _CHECKS_H

#include "consts_types.h"
#include "shared.h"

class Check
{
public:
  // changes the move struct fields to MOVE
  // if there are valid moves
  void checkMove(int8_t pos, move_st &moves);
  // changes the move struct fields to CAPTURE
  // if there are valid captures
  void checkCapture(int8_t pos, move_st &moves);
  // removes backward moves if the pieces are not king
  void checkBackwards(int8_t pos, move_st &moves);
  // if the struct has moves
  bool hasMoves(const move_st &moves);
  // if the struct has captures
  bool hasCaptures(const move_st &moves);

private:
  // checks if the piece is on the edges of the board
  void edge(int8_t p, move_st &moves);
  // checks if there are empty tiles next
  // to the piece on the board
  void empty(int8_t p, move_st &moves);
};

#endif