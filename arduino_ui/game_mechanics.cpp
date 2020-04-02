#include "game_mechanics.h"

extern shared_vars shared;

/* 
int8_t checkMustCapture(int8_t *capture):
Moves the positions of the pieces that 
can capture in the capture array and
returns the number of pieces that can capture
*/
int8_t checkMustCapture(int8_t *capture) {
  int8_t capp = 0; // number of pieces that can capture
  for (int i = 0; i < c::b_size; i++) {
    if (board(i) == PLAYER || board(i) == PK) {
      move_st moves = c::empty_m;
      // check which pieces can capture
      check::capture(i, moves);
      check::backwards(i, moves);
      if (has::captures(moves)) {
        capture[capp] = i;
        capp++;
      }
    }
  }
  return capp;
}

// show/hide which pieces can capture
void showCap(int8_t *capture, int8_t capp, bool show) {

  for (int i = 0; i < capp; i++) {
    if (show) {
      // show that the piece can capture
      draw::highlight(capture[i], true);
    } else {
      // redraw the piece to remove highlight
      draw::piece(capture[i]);
    }
  }
}

void attemptMove( selected& pieceSel, int8_t newPos, 
                  move_st& moves, move type,
                  int8_t *capture, int8_t capp) {
  // do nothing if no piece was selected
  if (pieceSel == PIECE) {
    // check if the moves are legal for this piece
    move legal = nsmove::legal(shared.selected, newPos, moves); 
    if (legal == type) {
      draw::unhighlight(shared.selected); // remove move marks
      if (type == MOVE) {
        nsmove::piece(shared.selected, newPos); // move piece
      } else {
        // unhighlight the pieces that could capture
        showCap(capture, capp, false);
        nsmove::capture(shared.selected, newPos);
      }
      shared.selected = -1; // now no piece is selected
      pieceSel = DONE; // done moving
    }
  }
}

// implements must capture rule
// returns true if the player had to capture
bool mustCapture() {
  int8_t capture[c::num_pcs];
  // number of pieces that can capture
  // with capture array listing the positions
  int8_t capp = checkMustCapture(capture); 
  
  // if there are no captures, move on to just moves
  if (capp == 0) {return false;}  
  // else, make the player capture
  selected pieceSel = NO_PIECE;
  move_st moves;
  showCap(capture, capp);
  while (pieceSel != DONE) {
    chooseMove(pieceSel, moves, CAPTURE, capture, capp);
  }
  return true;
}

// lets player choose a piece to move
void chooseMove(selected& pieceSel, move_st& moves, 
                move type, int8_t *capture, int8_t capp) {
  int8_t pos = nspiece::touch();
  // loop again if nothing was touched
  if (pos < 0) {return;} 
  
  // selecting a new piece
  if (board(pos) == PK || board(pos) == PLAYER) {
    if (nsmove::can_move(pos, moves, type)) {
      // do nothing if same piece was selected
      if (pos == shared.selected) {return;}
      // unhighlights old piece and its moves
      draw::unhighlight(pos);
      shared.selected = pos;
      nsmove::show(pos, moves); // show moves on board
      pieceSel = PIECE; // now a piece is selected
    }
  } else if (board(pos) == EMPTY) {
    // now check if the move is valid
    attemptMove(pieceSel, pos, moves, type, capture, capp);
  }
}