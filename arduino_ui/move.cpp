#include "move.h"

extern sharedVars shared;

// captures a piece
void nsmove::capture(Piece &piece, int8_t newPos) {
  int8_t os[4]; tileOS(piece.pos, os); // set tile offsets
  int8_t dg[] = {-9, -7, 7, 9};
  for (int i = 0; i < 4; i++) {
    // checks which direction the capturing piece jumped to
    if (newPos - piece.pos == dg[i]) {
      // remove captured piece from the board
      nspiece::remove(piece.pos + os[i]); 
      break;
    }
  }  
  nsmove::piece(piece.pos, newPos);
  nsmove::chain(piece); // checks for capture chain
}

void nsmove::chain(Piece &piece) {
  moveSt moves = {NOT, NOT, NOT, NOT};
  check::capture(piece, moves);
  // do nothing if there are no moves
  if (!has::captures(moves)) {return;}

  // highlight possible moves
  draw::highlight(piece);
  nsmove::show(piece.pos, moves);
  int8_t pos = nspiece::touch();
  // waits for the player to make a legal move
  while (!nsmove::legal(piece, pos, moves)) {
    pos = nspiece::touch();  
  }
  draw::unhighlight(piece);
  // recursively calls capture piece until 
  // there are no valid captures
  nsmove::capture(piece, pos);
}

// checks if the selected move is legal
move nsmove::legal(const Piece &piece, int8_t newPos, const moveSt& moves) {
  int8_t os[4]; tileOS(piece.pos, os); // adjust adjacent tile offsets
  // CAPTURES
  if ((moves.UL == CAPTURE && newPos == piece.pos - 9) ||
      (moves.UR == CAPTURE && newPos == piece.pos - 7) ||
      (moves.DL == CAPTURE && newPos == piece.pos + 7) ||
      (moves.DR == CAPTURE && newPos == piece.pos + 9)) {return CAPTURE;}
  // MOVES
  if ((moves.UL == MOVE && newPos == piece.pos + os[0]) ||
      (moves.UR == MOVE && newPos == piece.pos + os[1]) ||
      (moves.DL == MOVE && newPos == piece.pos + os[2]) ||
      (moves.DR == MOVE && newPos == piece.pos + os[3])) {return MOVE;}
  // piece can't move to the selected position
  return NOT;
}

// moves a piece from one position to another
void nsmove::piece(int8_t oldPos, int8_t newPos) {
  Piece* piece = nspiece::find(oldPos);
  // update piece's position in the board
  piece->pos = newPos;
  // checks for promotion
  if (!piece->king) {
    // promotion if a piece reaches the other side of the board
    if ((piece->side == BOT && newPos >= 28 && newPos < 32) ||
        (piece->side == PLAYER && newPos >= 0 && newPos < 4)) {
      piece->king = true;
      tile newType = (piece->side == BOT) ? BK : PK;
      piece->side = newType
      // converts to king piece on the board
      shared.board[piece->pos] = newType;
    }
  }
  // now tile is empty
  draw::clear(oldPos);
  // draw piece in new position
  draw::piece(*piece);
  // update board
  shared.board[oldPos] = EMPTY;
  shared.board[newPos] = piece->side;
}

// show valid moves on the screen
void nsmove::show(int8_t pos, const moveSt& moves) {
  using draw::mark;
  // adjacent tile offsets vary depending on row
  int8_t os[4]; tileOS(pos, os);

  // piece moves
  if (moves.UL == MOVE) {mark(pos + os[0]);}
  if (moves.UR == MOVE) {mark(pos + os[1]);}
  if (moves.DL == MOVE) {mark(pos + os[2]);}
  if (moves.DR == MOVE) {mark(pos + os[3]);}
  // piece captures
  if (moves.UL == CAPTURE) {mark(pos - 9);}
  if (moves.UR == CAPTURE) {mark(pos - 7);}
  if (moves.DL == CAPTURE) {mark(pos + 7);}
  if (moves.DR == CAPTURE) {mark(pos + 9);}

}

// shows the player where to move the piece
// returns true if a piece can move/capture
bool nsmove::canMove( int8_t piecePos, moveSt& moves, 
                      tile currentPlayer, move type) {

  Piece *piece = nspiece::find(piecePos);
  moveSt temp = moves; // keep previous moveset
  moves = {NOT, NOT, NOT, NOT};
  if (type == MOVE) {
    check::move(*piece, moves); // checks for valid moves
  } else if (type == CAPTURE) {
    check::capture(*piece, moves); // checks for valid captures
  }

  check::backwards(*piece, moves); // backwards check
  if (has::moves(moves) || has::captures(moves)) {
    draw::highlight(*piece);
    return true;
  }
  moves = temp; // revert to previous moveset
  return false;
}