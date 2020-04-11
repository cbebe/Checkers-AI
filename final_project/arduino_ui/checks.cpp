// ---------------
// checks.cpp
// ---------------
// Contains all functions that check for moves
//

#include "checks.h"

extern shared_vars shared;

// removing backward moves or captures 
void check::backwards(int8_t pos, move_st& moves) {
  Piece p = board(pos);
  // non-king pieces cannot move backwards
  // bot side cannot move up
  // player side cannot move down
  if (p == BOT) {
    moves.m[0] = NOT;
    moves.m[1] = NOT;
  } else if (p == PLAYER) {
    moves.m[2] = NOT;
    moves.m[3] = NOT;
  }
}

// checks if the piece is on the edges of the board
void edge(int8_t p, move_st& moves) {
  // do nothing if captured
  if (p < 0 || p > 31) {return;}
  if ((p - 4) % 8 == 0) { // left
    moves.m[0] = NOT; moves.m[2] = NOT;
  } else if ((p - 3) % 8 == 0) { // right
    moves.m[1] = NOT; moves.m[3] = NOT;
  }
  if (p < 4) { // top
    moves.m[0] = NOT; moves.m[1] = NOT;
  } else if (p > 27) { // bottom
    moves.m[2] = NOT; moves.m[3] = NOT;
  }
}

// checks for enemy pieces to capture
void check::capture(int8_t pos, move_st &moves) {
  // do nothing if out of bounds
  if (pos < 0 || pos > 31) {return;}

  // determines offset of tiles
  int8_t os[4]; 
  tileOS(pos, os); 
  // change the enemy depending on the piece's side
  Piece enemy = (board(pos) == BOT || board(pos) == BK) ? PLAYER : BOT;
  Piece enemyk = (enemy == BOT) ? BK : PK;

  /* checks for adjacent enemy pieces
  and empty tiles behind those pieces

  the empty tile might not be diagonal to the piece 
  on specific positions on the board
  these checks are for those positions */
  bool left = pos % 8 == 0;
  bool right = (pos - 7) % 8 == 0;
  // moves : UL UR DL DR
  for (int i = 0; i < 4; i++) {
    Piece t = board(pos + os[i]); // target
    if ((t == enemy || t == enemyk) && 
        board(pos + c::dg[i]) == EMPTY) {
        moves.m[i] = CAPTURE;
      // disable right moves if piece is on the right
      // disable left moves if piece is on the left
      if ((right && (i % 2)) || (left && !(i % 2))) {
        moves.m[i] = NOT;
      }
    }
  }

  // final edge check
  edge(pos, moves);
}

// checks if there are empty tiles next 
// to the piece on the board
void empty(int8_t p, move_st& moves) {
  // adjacent tile offsets are different depending on row
  int8_t os[4]; tileOS(p, os);
  for (int i = 0; i < 4; i++){
    if (board(p + os[i]) == EMPTY) {moves.m[i] = MOVE;}
  }
}

// checks for moves that can be made by the piece
void check::move(int8_t pos, move_st& moves) {
  // do nothing if out of bounds
  if (pos >= 0 && pos < 32) {
    empty(pos, moves); // checks for empty tiles
    // removes moves if pieces are on the edge
    edge(pos, moves); 
  } 
}

// check if there are valid captures
bool has::captures(const move_st &moves) {
  for (int i = 0; i < 4; i++) {
    if (moves.m[i] == CAPTURE) return true;
  }
  return false;
}

// check if there are valid moves
bool has::moves(const move_st& moves) {
  for (int i = 0; i < 4; i++) {
    if (moves.m[i] == MOVE) return true;
  }
  return false;
}
