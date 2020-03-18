#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "consts_types.h"
#include "pieces.h"
#include "touchs.h"

// shared variables
shared_vars shared;
// display and touch screen init
MCUFRIEND_kbv tft;


#define BOARD_DARK 19458 // colours for game board
#define BOARD_LIGHT 57113 // please change i don't like

/* int8_t touchPiece():
Determines which position of board that was touched
Returns -1 if the board is untouched
or a light tile was touched in the board
Returns -2 if out of bounds */

int8_t touchPiece() {
  screenPos tp = processTouchScreen();
  // if touch screen was untouched or out of bounds
  if (tp.x == UNTOUCHED){
    return -1;
  } else if ((tp.y > 300 && tp.y < 20) || (tp.x > 380 && tp.x < 100)) {
    return -2;
  }


  /* NOTE: The math here might be a bit hard to understand
  so just imagine the 8x8 board divided into 16 regions
  and those 16 regions each have a 2x2 matrix.
  The first two operations (fsRow and fsCol) determine which
  part of a matrix was touched. The second two then determine 
  which region in the 4x4 matrix. The position will then be 
  calculated in terms of these values.*/
 
  // remove board offset
  tp.x -= 100; tp.y -= 20;

  // calculation for 2x2 matrix

  // determine if first (0) or second (1) row was touched
  int8_t fsRow = (tp.y % (B_SQ * 2)) / B_SQ;
  // determine if first (0) or second (1) column was touched
  int8_t fsCol = (tp.x % (B_SQ * 2)) / B_SQ;

  // calculation for 4x4 matrix

  // determines which region of the board was touched
  int8_t regY = tp.y / (B_SQ * 2); 
  int8_t regX = tp.x / (B_SQ * 2); 
  // multiplication is logically the same as and
  // addition is logically the same as or
  if ((fsRow * fsCol) == 1 || 
      (fsRow + fsCol) == 0) {
    // a light tile was touched
    return -1;
  }
  
  return regX + (8 * regY) + (4 * fsRow);
}

bool menuScreen() {
  tft.fillRect(100,100, 100, 100, TFT_WHITE);
  bool touch = true;
  screenPos t;
  while (touch) {
    t = processTouchScreen();
    if (t.x > UNTOUCHED) {
      touch = false;
    }
  }
  return true;
}

// initialize game
void gameInit(bool start) {
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
    shared.gamePieces[i] = {1, false, i};
    // player pieces
    shared.gamePieces[i + NUM_PIECES] = {0, false, i + 20};
    
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
    shared.board[i + NUM_PIECES] = PLAYER;
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
  tft.fillScreen(TFT_BLACK);
  

  Serial.begin(9600);
  Serial.flush();

  // initialize SD card
  if (!SD.begin(SD_CS)) {
    while (1) {};    // Just wait, stuff exploded.
  }
}

void choosePiece() {
  int8_t piecePos;
  while (piecePos != -2) {
    piecePos = touchPiece();
    if (piecePos >= 0) {
      shared.tft->println(piecePos);

    }
    delay(500);
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