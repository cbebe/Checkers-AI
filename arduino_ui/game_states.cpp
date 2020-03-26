#include "game_states.h"

extern sharedVars shared;

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
  shared.tft->fillScreen(TFT_BLACK);
  // draw checkers board
  shared.tft->fillRect(off_x, off_y, board_w, board_w, board_dark);
  // print the light tiles
  for (int8_t i = 0; i < 8; i += 2) {
    for (int8_t j = 0; j < 8; j += 2) {
      shared.tft->fillRect( off_x + (i*board_sq), off_y + (j*board_sq), 
                            board_sq, board_sq, board_light);
      shared.tft->fillRect( off_x + ((i+1)*board_sq), off_y + ((j+1)*board_sq), 
                            board_sq, board_sq, board_light);
    }
  }
  // initialize empty spaces on board
  for (int8_t i = 12; i < 20; i++) {
    shared.board[i] = EMPTY;
  }
  
  // places pieces on board
  for (int8_t i = 0; i < num_pieces; i++) {
    // bot pieces
    shared.gamePieces[i] = {1, BOT, false, i};
    // player pieces
    shared.gamePieces[i + num_pieces] = {0, PLAYER, false, i + 20};
    
    // change colour if player chose black
    if (start) {
      shared.gamePieces[i].colour = 0;
      shared.gamePieces[i+ num_pieces].colour = 1;
    }
    // draw pieces on board
    draw::piece(shared.gamePieces[i]);
    draw::piece(shared.gamePieces[i + num_pieces]);
    // place pieces in board array
    shared.board[i] = BOT;
    shared.board[i + 20] = PLAYER;
  }
  // dummy piece
  shared.gamePieces[dummy] = {0, EMPTY, false, -1}; 
}

win endCheck() {

}

// checks if any of the player's/bot's pieces must capture
void checkMustCapture(bool turn, bool *capture) {
  using c::num_pieces;
  // starts the index at start
  // depending on which side the current player is
  int8_t start = turn ? num_pieces : 0;
  for (int i = start; i < start + num_pieces; i++) {
    Piece *piece = &shared.gamePieces[i];
    moveSt moves = {NOT, NOT, NOT, NOT};
    check::capture(*piece, moves);
    // fill array with bool
    capture[i % num_pieces] = has::captures(moves);
  }
}

void mustCapture(bool turn) {
  bool capture[c::num_pieces];
  checkMustCapture(turn, capture);
  bool check = false;
  for (int i = 0; i < c::num_pieces; i++) {
    if (capture[i]) {
      check = true;
      break;
    }
  }
  // if there are no captures, move on to just moves
  if (!check) {return;}
  // else, make the player capture
  selected pieceSel = NO_PIECE;
}

void doTurn(bool turn) {
  mustCapture(turn);
  selected pieceSel = NO_PIECE;
  moveSt moves;
  while(pieceSel != DONE) {
    nspiece::choose(pieceSel, turn, moves);
  }
}

void game(bool start) {
  // true is player's turn, bot is false 
  bool turn = true; 
  if (!start){
    turn = false;
  }
  win state = NONE;
  // goes on until the end
  while (state == NONE) {
    doTurn(turn);
    state = endCheck();
    turn = !turn;
  }
}