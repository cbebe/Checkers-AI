#include "game_states.h"

extern shared_vars shared;

void processTS(bool start, int difficulty) {
  while (touch::process().x == touch::untch);
}

// sets up menu screen
bool menuScreen() {
  // get tft screen
  MCUFRIEND_kbv tft = *shared.tft;
  using namespace c;
  
  tft.fillScreen(TFT_BLACK);
  tft.fillRect(off_x, off_y, b_width, b_width, TFT_WHITE);

  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);
  tft.setCursor(off_x + b_sq, off_y + b_sq);
  tft.print("Difficulty:");

  tft.setCursor(off_x + b_sq, off_y + b_sq * 4);
  tft.print("First Move:");

  tft.setCursor(off_x + b_sq * 3, off_y + b_width - b_sq);
  tft.print("START");

  bool start; int difficulty;
  processTS(start, difficulty);
  return start;
}

// initialize game
void gameInit() {
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
  if (must_capture()) {return;}
  // else just move
  selected pieceSel = NO_PIECE;
  move_st moves;
  
  while(pieceSel != DONE) {
    choose_move(pieceSel, moves);
  }
}

// check if all pieces are captured
Win checkPieces() {
  int8_t bot = 0, player = 0;
  for (int i = 0; i < c::b_size; i++) {
    Piece p = board(i);
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
bool noMoves(Piece side) {
  // king piece
  Piece sidek = (side == BOT) ? BK : PK;
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
Win endCheck(Piece side) {
  if (noMoves(side)) {return DRAW;}
  return checkPieces();
}

void game_result(Win state) {
  if (state == PLAYERW) {
    db("PLAYER WON! TOUCH TO PLAY AGAIN.");
  } else if (state == BOTW) {
    db("BOT WON! TOUCH TO PLAY AGAIN.");
  } else if (state == DRAW) {
    db("DRAW! TOUCH TO PLAY AGAIN.");
  }
}

void game(bool start) {
  // true is player's turn, bot is false 
  Win state = NONE;
  // goes on until the end
  while (state == NONE) {
    comm::receive_board();
    doTurn();
    state = endCheck(BOT);
    if (state == NONE) {
      comm::send_board();
      state = endCheck(PLAYER);
    }
  }
  game_result(state);
  delay(1000);
  while (touch::process().x == touch::untch);
  comm::end_game();
}