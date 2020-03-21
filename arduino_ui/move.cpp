#include "move.h"

extern sharedVars shared;

// a second check for capture moves 
// WORK IN PROGRESS
void validateCapture(const Piece& piece, moveSt& moves) {
  int8_t p = piece.pos;
  // checks for UL
  if (moves.UL == CAPTURE) {
    if (p >= 5 && p <= 7) {
      moves.UL == NOT;
    }
  }
  if (moves.UR == CAPTURE) {
    if (p >= 5 && p <= 7) {
      moves.UL == NOT;
    }
  }
}

// checks for enemy pieces to capture
void captureCheck(const Piece& piece, moveSt& moves) {
  int8_t os[4];
  int8_t p = piece.pos;
  adjTileOS(p, os); // determines offset of tiles
  tile enemy = BOT;
  if (piece.side == BOT) {
    enemy = PLAYER;
  }

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
  validateCapture(piece, moves);
}

// checks if there are empty tiles next 
// to the piece on the board
void emptyCheck(int8_t p, moveSt& moves) {
  // adjacent tile offsets are different depending on row
  int8_t os[4];
  adjTileOS(p, os);

  if (board(p + os[0]) == EMPTY) {moves.UL = MOVE;}
  if (board(p + os[1]) == EMPTY) {moves.UR = MOVE;}
  if (board(p + os[2]) == EMPTY) {moves.DL = MOVE;}
  if (board(p + os[3]) == EMPTY) {moves.DR = MOVE;}
}

// checks if the piece is on the edges of the board
void edgeCheck(int8_t p, moveSt& moves) {
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

// checks for moves that can be made by the piece
void moveCheck(const Piece &piece, moveSt& moves) {
  int8_t p = piece.pos; 
  emptyCheck(p, moves); // checks for empty tiles
  edgeCheck(p, moves); // removes edge moves

  if (!piece.king) {
    // player non-king can only move up
    if (piece.side == PLAYER) {
      moves.DL = NOT;
      moves.DR = NOT;
    }
    // bot non-king can only move down
    if (piece.side == BOT) {
      moves.UL = NOT;
      moves.UR = NOT;
    }
  }
}

// function to see if there are legal moves
// returns a struct of legal moves
moveSt findMove(const Piece &piece, const tile& currentPlayer) {
  // create move Struct  
  moveSt valid = {NOT, NOT, NOT, NOT};
  moveCheck(piece, valid);
  return valid;
}

// check if there are valid moves
bool hasMoves(moveSt moves) {
  if (moves.UL != NOT) {return true;}
  if (moves.UR != NOT) {return true;}
  if (moves.DL != NOT) {return true;}
  if (moves.DR != NOT) {return true;}
  return false;
}

void markMove(int8_t pos) {
  screenPos dp = piecePosition(pos);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad/2, TFT_RED);
  shared.tft->drawCircle(dp.x, dp.y, c::pc_rad/2 + 1, TFT_RED);
}

// show valid moves on the screen
void showMoves(int8_t pos, const moveSt& moves) {
  // adjacent tile offsets vary depending on row
  int8_t os[4];
  adjTileOS(pos, os);

  // piece moves
  if (moves.UL == MOVE) {markMove(pos + os[0]);}
  if (moves.UR == MOVE) {markMove(pos + os[1]);}
  if (moves.DL == MOVE) {markMove(pos + os[2]);}
  if (moves.DR == MOVE) {markMove(pos + os[3]);}
  // piece captures
  if (moves.UL == CAPTURE) {markMove(pos - 9);}
  if (moves.UR == CAPTURE) {markMove(pos - 7);}
  if (moves.DL == CAPTURE) {markMove(pos + 7);}
  if (moves.DR == CAPTURE) {markMove(pos + 9);}

}

// shows the player where to move the piece
// returns true if a piece can move
bool pieceCanMove(int8_t piecePos, moveSt& moves, tile currentPlayer) {
  Piece *piece = &shared.gamePieces[pieceIndex(piecePos)];
  moveSt temp = moves; // keep previous moveset
  moves = findMove(*piece, currentPlayer);
  if (hasMoves(moves)) {
    highlightPiece(*piece);
    return true;
  }
  moves = temp; // revert to previous moveset
  return false;
}