#include "move.h"

extern sharedVars shared;

// checks if there are empty tiles next 
// to the piece on the board
void moveCheck(int8_t p, moveSt& moves) {
  if (shared.board[p - 3] == EMPTY) {
    moves.UL = MOVE;
  }
  if (shared.board[p - 4] == EMPTY) {
    moves.UR = MOVE;
  }
  if (shared.board[p + 4] == EMPTY) {
    moves.DL = MOVE;
  }
  if (shared.board[p + 3] == EMPTY) {
    moves.DR = MOVE;
  }
}

// checks if the piece is on the edges of the board
void edgeCheck(int8_t p, moveSt& moves) {
  if ((p - 4) % 8 == 0) { // left
    moves.UL = NOT;
    moves.DL = NOT;
  } else if ((p - 3) % 8 == 0) { // right
    moves.UR = NOT;
    moves.DR = NOT;
  }
  if (p < 4) { // top
    moves.UL = NOT;
    moves.UR = NOT;
  } else if (p > 27) { // bottom
    moves.DL = NOT;
    moves.DR = NOT;
  }
}

// function to see if there are legal moves
// returns a struct of legal moves
moveSt findMove(Piece piece) {
  // cast piece.pos to 16-bit int for operations
  int8_t p = piece.pos; 
  moveSt valid = {NOT, NOT, NOT, NOT};
  
  moveCheck(p, valid); // checks for valid moves
  edgeCheck(p, valid); // removes edge moves

  if (!piece.king) {
    // player non-king can only move up
    if (piece.side == PLAYER) {
      valid.DL = NOT;
      valid.DR = NOT;
    }
    // bot non-king can only move down
    if (piece.side == BOT) {
      valid.UL = NOT;
      valid.UR = NOT;
    }
  }

  // king can move either direction
  return valid;
}

// check if there are valid moves
bool hasMoves(moveSt moves) {
  if (moves.UL != NOT) return true;
  if (moves.UR != NOT) return true;
  if (moves.DL != NOT) return true;
  if (moves.DR != NOT) return true;
  return false;
}

void highlightMove(int8_t position) {

}

// show valid moves
void showMoves(Piece piece, moveSt moves) {
  if (moves.UL == MOVE) {
    highlightMove(piece.pos - 4);
  }
}

// lets player choose where to move the piece
// returns true if the piece is moved
bool makeMove(int8_t piecePos) {
  Piece piece = findPiece(piecePos);
  highlightPiece(piece);
  
  // find tiles where a move can be made
  findMove(piece);
}