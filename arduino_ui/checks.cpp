#include "checks.h"

extern sharedVars shared;

// removing backward moves or captures 
void check::backwards(const Piece& piece, moveSt& moves) {
  // bot side cannot move up
  // player side cannot move down
  if (piece.side == BOT) {
    moves.UL = NOT;
    moves.UR = NOT;
  } else {
    moves.DL = NOT;
    moves.DR = NOT;
  }
}

// checks if the piece is on the edges of the board
void edge(int8_t p, moveSt& moves) {
  // do nothing if captured
  if (p < 0) {return;}
  if ((p - 4) % 8 == 0) { // left
    moves.UL = NOT; moves.DL = NOT;
  } else if ((p - 3) % 8 == 0) { // right
    moves.UR = NOT; moves.DR = NOT;
  }
  if (p < 4) { // top
    moves.UL = NOT; moves.UR = NOT;
  } else if (p > 27) { // bottom
    moves.DL = NOT; moves.DR = NOT;
  }
}

// checks for enemy pieces to capture
void check::capture(const Piece &piece, moveSt &moves) {
  // do nothing if piece is captured
  if (piece.pos == -1) {return;}
  int8_t p = piece.pos;
  // determines offset of tiles
  int8_t os[4]; tileOS(p, os); 
  // change the enemy depending on the piece's side
  tile enemy = (piece.side == BOT) ? PLAYER : BOT;

  // checks for adjacent enemy pieces
  // and empty tiles behind those pieces
  if (board(p + os[0]) == enemy && 
      board(p - 9) == EMPTY) {
      moves.UL = CAPTURE;
  }
  if (board(p + os[1]) == enemy && 
      board(p - 7) == EMPTY) {
      moves.UR = CAPTURE;
  }
  if (board(p + os[2]) == enemy &&
      board(p + 7) == EMPTY) {
      moves.DL = CAPTURE;
  }
  if (board(p + os[3]) == enemy &&
      board(p + 9) == EMPTY) {
      moves.DR = CAPTURE;  
  }
  
  // the empty tile might not be diagonal to the piece 
  // on specific positions on the board
  // these checks are for those positions 
  bool left = p % 8 == 0;
  bool right = (p - 7) % 8 == 0;
  if (moves.UL == CAPTURE && left) {moves.UL = NOT;}
  if (moves.DL == CAPTURE && left) {moves.DL = NOT;}
  if (moves.UR == CAPTURE && right) {moves.UR = NOT;}
  if (moves.DR == CAPTURE && right) {moves.DR = NOT;}

  // final edge check
  edge(p, moves);
}

// checks if there are empty tiles next 
// to the piece on the board
void empty(int8_t p, moveSt& moves) {void captureCheck(const Piece &piece, moveSt& moves);
  // adjacent tile offsets are different depending on row
  int8_t os[4]; tileOS(p, os);

  if (board(p + os[0]) == EMPTY) {moves.UL = MOVE;}
  if (board(p + os[1]) == EMPTY) {moves.UR = MOVE;}
  if (board(p + os[2]) == EMPTY) {moves.DL = MOVE;}
  if (board(p + os[3]) == EMPTY) {moves.DR = MOVE;}
}


// checks for moves that can be made by the piece
void check::move(const Piece &piece, moveSt& moves) {
  int8_t p = piece.pos; 
  if (p < 0) {return;} // do nothing if captured
  empty(p, moves); // checks for empty tiles

  // non-king pieces cannot move backwards
  if (!piece.king) {
    check::backwards(piece, moves);
  }
  // removes moves if pieces are on the edge
  edge(p, moves);
}

bool has::captures(const moveSt &moves) {
  if ((moves.UL == CAPTURE) ||
      (moves.UR == CAPTURE) ||
      (moves.DL == CAPTURE) ||
      (moves.DR == CAPTURE)) {return true;}
  return false;
}

// check if there are valid moves
bool has::moves(const moveSt& moves) {
  if ((moves.UL == MOVE) ||
      (moves.UR == MOVE) ||
      (moves.DL == MOVE) ||
      (moves.DR == MOVE)) {return true;}
  return false;
}
