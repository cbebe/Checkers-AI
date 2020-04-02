#include "game_states.h"

extern shared_vars shared;

// not really important rn
bool menuScreen() {
  int off = 100;
  shared.tft->fillRect(98 + off,98 + off, 109, 18, TFT_WHITE);
  shared.tft->setCursor(100 + off, 100 + off);
  shared.tft->setTextColor(TFT_BLACK); 
  shared.tft->setTextSize(2);
  shared.tft->println("RESETTING");
  screenPos t = touch::process();
  while (t.x == touch::untch) {
    t = touch::process();
  }
  shared.tft->setTextSize(1);
  shared.tft->setTextColor(TFT_WHITE);
  shared.tft->setCursor(0,0);
  return true;
}

// initialize game
void gameInit(bool start) {
  // namespace is only used when not using 
  // would lead to lesser readability
  using namespace c;
  MCUFRIEND_kbv *tft = shared.tft;
  tft->fillScreen(TFT_BLACK);
  // draw checkers board
  tft->fillRect(off_x, off_y, b_width, b_width, b_dark);
  // print the light tiles
  for (int8_t i = 0; i < 8; i += 2) {
    for (int8_t j = 0; j < 8; j += 2) {
      tft->fillRect(off_x + (i*b_sq), 
                    off_y + (j*b_sq), 
                    b_sq, b_sq, b_light);
      tft->fillRect(off_x + ((i+1)*b_sq), 
                    off_y + ((j+1)*b_sq), 
                    b_sq, b_sq, b_light);
    }
  }
  // initialize empty spaces on board
  for (int8_t i = num_pcs; i < 20; i++) {
    shared.board[i] = EMPTY;
  }
  
  // places pieces on board
  for (int8_t i = 0; i < num_pcs; i++) {
    
    // place pieces in board array
    // bot pieces
    shared.board[i] = BOT;
    // player pieces
    shared.board[i + 20] = PLAYER;
    
    // draw pieces on board
    draw::piece(i);
    draw::piece(i + 20);
  }
}

void doTurn() {
  // will skip moves if the player must capture
  if (mustCapture()) {return;}
  // else just move
  selected pieceSel = NO_PIECE;
  move_st moves;
  
  while(pieceSel != DONE) {
    chooseMove(pieceSel, moves);
  }
}

// check if all pieces are captured
win checkPieces() {
  int8_t bot = 0, player = 0;
  for (int i = 0; i < c::b_size; i++) {
    piece_t p = board(i);
    // counts the number of pieces
    // for each player
    if (p != EMPTY) {
      if (p == PK || p == PLAYER) {
        player++;
      } else if (p == BK || p == BOT) {
        bot++;
      }
    }
  }
  
  if (bot == 0) {
    return PLAYERW;
  } else if (player == 0) {
    return BOTW;
  }
  return NONE; // continue game
}

// check if pieces can move
bool noMoves(piece_t side) {
  // king piece
  piece_t sidek = (side == BOT) ? BK : PK;
  for (int8_t i = 0; i < c::b_size; i++) {
    if (board(i) == side || board(i) == sidek) {
      move_st moves = c::empty_m;
      // check for valid moves or captures
      if (nsmove::can_move(i, moves, NOT)) {
        return false;
      }
    }
  }
  // no more moves
  return true;
}

// check for endgame conditions
win endCheck(piece_t side) {
  if (noMoves(side)) {return DRAW;}
  return checkPieces();
}

void game(bool start) {
  // true is player's turn, bot is false 
  win state = NONE;
  // goes on until the end
  while (state == NONE) {
    doTurn();
    state = endCheck(BOT);
    if (state != NONE) {
      comm::send_state();
      comm::get_move();
      state = endCheck(PLAYER);
    }
  }
}