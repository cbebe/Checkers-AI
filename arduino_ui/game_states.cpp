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
  screenPos t = processTouchScreen();
  while (t.x == UNTOUCHED) {
    t = processTouchScreen();
  }
  return true;
}

// initialize game
void gameInit(bool start) {

  shared.tft->fillScreen(TFT_BLACK);
  // draw checkers board
  shared.tft->fillRect(100,20,280,280, BOARD_DARK);
  // print the light tiles
  for (int i = 0; i < 8; i += 2) {
    for (int j = 0; j < 8; j += 2) {
      shared.tft->fillRect(100 + (i*B_SQ), 20 + (j*B_SQ), B_SQ, B_SQ, BOARD_LIGHT);
      shared.tft->fillRect(135 + (i*B_SQ), 55 + (j*B_SQ), B_SQ, B_SQ, BOARD_LIGHT);
    }
  }
  // initialize empty spaces on board
  for (int i = 12; i < 20; i++) {
    shared.board[i] = EMPTY;
  }
  
  // places pieces on board
  for (int8_t i = 0; i < NUM_PIECES; i++) {
    // bot pieces
    shared.gamePieces[i] = {1, BOT, false, i};
    // player pieces
    shared.gamePieces[i + NUM_PIECES] = {0, PLAYER, false, i + 20};
    
    // change colour if player chose black
    if (start) {
      shared.gamePieces[i].colour = 0;
      shared.gamePieces[i+ NUM_PIECES].colour = 1;
    }
    // draw pieces on board
    drawPiece(shared.gamePieces[i]);
    drawPiece(shared.gamePieces[i + NUM_PIECES]);
    // place pieces in board array
    shared.board[i] = BOT;
    shared.board[i + 20] = PLAYER;
  }
}

win endCheck() {

}


void doTurn(bool turn) {
  selected pieceSel = NO_PIECE;
  while(pieceSel != DONE) {
    choosePiece(pieceSel);
  }
}

void game(bool start) {
  // true is player's turn, bot is false 
  bool turn = true; 
  if (!start){
    turn = false;
  }
  while (true) {
    test();
  }
  win state = NONE;
  // goes on until the end
  while (state == NONE) {
    doTurn(turn);
    state = endCheck();
    turn = !turn;
  }
}