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

// determine position of piece that was touched
int8_t touchPiece() {
  tPoint tp = processTouchScreen();
  if (tp.x > UNTOUCHED && tp.y > UNTOUCHED) {
    // remove board offset
    tp.x -= 100; tp.y -= 20;
    int8_t group = 
  }
}

bool menuScreen() {
  tft.fillRect(100,100, 100, 100, TFT_WHITE);
  bool touch = true;
  tPoint t;
  while (touch) {
    t = processTouchScreen();
    if (t.x > UNTOUCHED) {
      touch = false;
    }
  }
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

  // places pieces on board
  for (int8_t i = 0; i < NUM_PIECES; i++) {
    // bot pieces
    shared.gamePieces[i] = {1, false, i};
    // player pieces
    shared.gamePieces[i + NUM_PIECES] = {0, false, i + 20};
    // change colour if player chose black
    if (start) {
      shared.gamePieces[i].colour = 0;
      shared.gamePieces[i+1].colour = 1;
    }
    drawPiece(shared.gamePieces[i]); 
    drawPiece(shared.gamePieces[i + NUM_PIECES]);
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


int main() {
  // set up Arduino
  setup();
  
  while (true) {
    bool start = menuScreen();
    gameInit(start);
  }
  return 0;
}