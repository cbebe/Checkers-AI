#include "pieces.h"

extern sharedVars shared; 

/* int8_t touchPiece():
Determines which position of board that was touched
Returns -1 if the board is untouched
or a light tile was touched in the board  
Returns -2 if touch was out of bounds of the board */
int8_t touchPiece() {
  // namespace only used when not using would
  // lead to lesser readability
  using namespace c;
  screenPos tp = touch::process();
  // if touch screen was untouched
  if (tp.x == touch::untch){return -1;} 
  // if touch screen was out of bounds
  if ((tp.y > off_y + board_w || tp.y < off_y) || 
      (tp.x > off_x + board_w || tp.x < off_x)) {return -2;}

  /* NOTE: The math here might be a bit hard to understand
  so just imagine the 8x8 board divided into 16 regions
  and those 16 regions each have a 2x2 matrix.
  The first two operations (fsRow and fsCol) determine which
  part of a matrix was touched. The second two then determine 
  which region in the 4x4 matrix. The position will then be 
  calculated in terms of these values.*/
 
  // remove board offset
  tp.x -= off_x; tp.y -= off_y;
  /* calculation for 2x2 matrix */

  // determine if first (0) or second (1) row was touched
  int8_t fsRow = (tp.y % (board_sq * 2)) / board_sq;
  // determine if first (0) or second (1) column was touched
  int8_t fsCol = (tp.x % (board_sq * 2)) / board_sq;

  /* calculation for 4x4 matrix */

  // determines which region of the board was touched
  int8_t regY = tp.y / (board_sq * 2); 
  int8_t regX = tp.x / (board_sq * 2); 

  // multiplication is logically the same as AND
  // addition is logically the same as OR
  // checks if a light tile was touched
  if ((fsRow * fsCol) == 1 || 
      (fsRow + fsCol) == 0) {return -1;}
  
  return regX + (8 * regY) + (4 * fsRow);
}

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

void nsmove::chain(Piece &piece) {
  moveSt moves = {NOT, NOT, NOT, NOT};
  check::capture(piece, moves);
  // do nothing if there are no moves
  if (!has::captures(moves)) {return;}

  // highlight possible moves
  draw::highlight(piece, false);
  nsmove::show(piece.pos, moves);
  int8_t pos = touchPiece();
  // waits for the player to make a legal move
  while (!nsmove::legal(piece, pos, moves)) {
    pos = touchPiece();  
  }
  draw::unhighlight(piece);
  // recursively calls capture piece until 
  // there are no valid captures
  nsmove::capture(piece, pos);
}

// lets player choose a piece to move
void nspiece::choose(selected& pieceSel, bool turn, moveSt& moves) {
  int8_t piecePos = touchPiece();
  // loop again if nothing was touched
  if (piecePos < 0) {return;} 

  // selecting a new piece
  tile currentPlayer = BOT;
  if (turn) {
    currentPlayer = PLAYER;
  }
  if (board(piecePos) == currentPlayer) {
    if (nsmove::canMove(piecePos, moves, currentPlayer)) {
      // do nothing if same piece was selected
      if (piecePos == shared.selected) {return;}
      // unhighlights old piece and its moves
      draw::unhighlight(*nspiece::find(shared.selected));
      shared.selected = piecePos;
      nsmove::show(piecePos, moves);
      pieceSel = PIECE; // now a piece is selected
    }
  } else if (board(piecePos) == EMPTY) {
    if (pieceSel == NO_PIECE) {return;}
    if (pieceSel == PIECE) {
      // check if the moves are legal for this piece
      Piece* piece = nspiece::find(shared.selected);
      move legal = nsmove::legal(*piece, piecePos, moves); 
      if(legal != NOT) {
        draw::unhighlight(*piece); // remove move marks
        if (legal == CAPTURE) {
          nsmove::capture(*piece, piecePos); // remove captured piece
        } else {
          nsmove::piece(piece->pos, piecePos); // move piece
        }
        shared.selected = -1; // now no piece is selected
        pieceSel = DONE; // done moving
      }
    }
  }
}

// find a piece's index on the board array
// in terms of position
// return dummy piece if not found
int8_t nspiece::index(int8_t pos) {
  if (pos < 0) {return c::dummy;}
  // find the piece in the board that matches the position
  for (int i = 0; i < c::num_pieces * 2; i++) {
    if (shared.gamePieces[i].pos == pos) {return i;}
  }
  return c::dummy;
}

// returns a pointer to the piece
Piece* nspiece::find(int8_t pos) {
  // Piece* ptr = 
  return &shared.gamePieces[nspiece::index(pos)];
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

// remove a piece from the board
void nspiece::remove(int8_t piecePos) {
  // piece is captured
  nspiece::find(piecePos)->pos = -1;
  draw::clear(piecePos);
  shared.board[piecePos] = EMPTY;
}

// shows the player where to move the piece
// returns true if a piece can move
bool nsmove::canMove(int8_t piecePos, moveSt& moves, tile currentPlayer) {
  Piece *piece = nspiece::find(piecePos);
  moveSt temp = moves; // keep previous moveset
  check::move(*piece, moves); // checks for valid moves
  if (has::moves(moves)) {
    draw::highlight(*piece, false);
    return true;
  }
  moves = temp; // revert to previous moveset
  return false;
}