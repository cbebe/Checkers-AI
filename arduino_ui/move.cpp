#include "move.h"

extern sharedVars shared;

// determines adjacent tile offset depending
// on which row the piece is in
void adjTileOS(int8_t p, int8_t *os) {
  // tile offsets {0:UL, 1:UR, 2:DL, 3:DR}
  os[0] = -5; os[2] = 3;
  os[1] = -4; os[3] = 4; 
  // second row has different offsets
  if ((p % 8)/ 4) {
    shared.tft->println("huh");
    for (int i = 0; i < 4; i++) {
      os[i] += 1;
    } 
  }
}

// a second check for capture moves 
void validateCapture(Piece& piece, moveSt& moves, bool &chain) {
  int8_t p = piece.pos;
  // checks for UL
  if (moves.UL == CAPTURE) {
    if (p >= 5 && p <= 7) {
      moves.UL == NOT;
    }
  } 
}


// checks for enemy pieces to capture
void captureCheck(Piece& piece, moveSt& moves, bool &chain) {
  int8_t os[4];
  int8_t p = piece.pos;
  adjTileOS(p, os); // determines offset of tiles
  tile enemy = BOT;
  if (piece.side == BOT) {
    enemy = PLAYER;
  }

  // checks for adjacent enemy pieces
  // and empty tiles behind those pieces
  if (shared.board[p + os[0]] == enemy &&
      shared.board[p - 9] == EMPTY) {
      moves.UL = CAPTURE;
  }
  if (shared.board[p + os[1]] == enemy && 
      shared.board[p - 7] == EMPTY) {
      moves.UR = CAPTURE;
  }
  if (shared.board[p + os[2]] == enemy &&
      shared.board[p + 7] == EMPTY) {
      moves.DL = CAPTURE;
  }
  if (shared.board[p + os[3]] == enemy &&
      shared.board[p + 9] == EMPTY) {
      moves.DR = CAPTURE;  
  }
  validateCapture(piece, moves, chain);
}


// checks if there are empty tiles next 
// to the piece on the board
void emptyCheck(int8_t p, moveSt& moves) {
  // adjacent tile offsets are different depending on row
  int8_t os[4];
  adjTileOS(p, os);

  if (shared.board[p + os[0]] == EMPTY) {moves.UL = MOVE;}
  if (shared.board[p + os[1]] == EMPTY) {moves.UR = MOVE;}
  if (shared.board[p + os[2]] == EMPTY) {moves.DL = MOVE;}
  if (shared.board[p + os[3]] == EMPTY) {moves.DR = MOVE;}
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
void moveCheck(Piece piece, moveSt& moves) {
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
moveSt findMove(Piece piece) {
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
  shared.tft->drawCircle(dp.x, dp.y, PC_RAD/2, TFT_RED);
  shared.tft->drawCircle(dp.x, dp.y, PC_RAD/2 + 1, TFT_RED);
}

// show valid moves on the screen
void showMoves(int8_t pos, moveSt& moves) {
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
bool pieceCanMove(int8_t piecePos) {
  if (piecePos >= 0) {      
    if (shared.board[piecePos] == PLAYER) {
      Piece piece = findPiece(piecePos);
      moveSt moves = findMove(piece);
      if (hasMoves(moves)) {
        highlightPiece(piece);
        showMoves(piecePos, moves);
        return true;
      }
    }
  }
  return false;
}