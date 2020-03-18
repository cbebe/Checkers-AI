#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "consts_types.h"
#include "pieces.h"
#include "touchs.h"
#include "game_mechanics.h"

// shared variables
sharedVars shared;
// display and touch screen init
MCUFRIEND_kbv tft;

// not really important rn
bool menuScreen() {
  tft.fillRect(100,100, 100, 100, TFT_WHITE);
  tft.setCursor(100, 100);
  tft.println("RESETTING");
  screenPos t = processTouchScreen();
  while (t.x == UNTOUCHED) {
    t = processTouchScreen();
  }
  return true;
}

// initialize game
void gameInit(bool start) {

  tft.fillScreen(TFT_BLACK);
  // draw checkers board
  tft.fillRect(100,20,280,280, BOARD_DARK);
  // print the light tiles
  for (int i = 0; i < 8; i += 2) {
    for (int j = 0; j < 8; j += 2) {
      tft.fillRect(100 + (i*B_SQ), 20 + (j*B_SQ), B_SQ, B_SQ, BOARD_LIGHT);
      tft.fillRect(135 + (i*B_SQ), 55 + (j*B_SQ), B_SQ, B_SQ, BOARD_LIGHT);
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

void setup() {
  // initialize Arduino
  init();

  // initialize display
  shared.tft = &tft;
	uint16_t ID = tft.readID();
	tft.begin(ID);
	tft.setRotation(1);

  

  Serial.begin(9600);
  Serial.flush();

  // initialize SD card
  if (!SD.begin(SD_CS)) {
    while (1) {};    // Just wait, stuff exploded.
  }
}

int main() {
  // set up Arduino
  setup();
  
  while (true) {
    bool start = menuScreen();
    gameInit(start);
    choosePiece();
  }
  return 0;
}