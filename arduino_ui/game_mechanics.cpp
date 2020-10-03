// ---------------
// game_mechanics.cpp
// ---------------
// Contains all functions related to game mechanics
//


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
void show_cap(int8_t *capture, int8_t capp, bool show) {

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

/* 
  void attempt_move():
  Checks if the move if valid
  sets pieceSel to DONE if move was valid
*/
void attempt_move(Selected& pieceSel, int8_t newPos, 
                  move_st& moves, move type,
                  int8_t *capture, int8_t capp) {
  // do nothing if no piece was selected
  if (pieceSel == PIECE) {
    // check if the moves are legal for this piece
    move legal = nsmove::legal(shared.currentPc, newPos, moves); 
    if (legal == type) {
      draw::unhighlight(shared.currentPc); // remove move marks
      if (type == MOVE) {
        nsmove::piece(shared.currentPc, newPos); // move piece
      } else {
        // unhighlight the pieces that could capture
        show_cap(capture, capp, false);
        nsmove::capture(shared.currentPc, newPos);
      }
      shared.currentPc = -1; // now no piece is selected
      pieceSel = DONE; // done moving
    }
  }
}

// implements must capture rule
// returns true if the player had to capture
bool must_capture() {
  int8_t capture[c::num_pcs];
  // number of pieces that can capture
  // with capture array listing the positions
  int8_t capp = checkMustCapture(capture); 
  
  // if there are no captures, move on to just moves
  if (capp == 0) {return false;}  
  // else, make the player capture
  Selected pieceSel = NO_PIECE;
  move_st moves;
  show_cap(capture, capp); // show which pieces can capture

  // waits until a valid capture is made
  while (pieceSel != DONE) {
    choose_move(pieceSel, moves, CAPTURE, capture, capp);
  }
  return true;
}

// lets player choose a piece to move
void choose_move(Selected& pieceSel, move_st& moves, 
                move type, int8_t *capture, int8_t capp) {
  int8_t pos = nspiece::touch();
  // loop again if nothing was touched
  if (pos < 0) {return;} 
  
  // selecting a new piece
  if (board(pos) == PK || board(pos) == PLAYER) {
    if (nsmove::can_move(pos, moves, type)) {
      draw::highlight(pos); // highlight a piece
      // do nothing if same piece was selected
      if (pos == shared.currentPc) {return;}
      // unhighlights old piece and its moves
      draw::unhighlight(shared.currentPc);
      shared.currentPc = pos;
      nsmove::show(pos, moves); // show moves on board
      pieceSel = PIECE; // now a piece is selected
    }
  } else if (board(pos) == EMPTY) {
    // now check if the move is valid
    attempt_move(pieceSel, pos, moves, type, capture, capp);
  }
}