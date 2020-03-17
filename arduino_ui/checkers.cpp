#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "pieces.h"

#define SD_CS 10

// display init
MCUFRIEND_kbv tft;
Piece gamePieces[24];

#define BOARD_DARK 19458 // colours for game board
#define BOARD_LIGHT 57113 // please change i don't like


bool menuScreen() {
  
}

void gameStart(bool start) {

  // places pieces on board
  for (uint8_t i = 0; i < 12; i++) {
    // bot pieces
    gamePieces[i] = {1, false, i};
    // player pieces
    gamePieces[i + 12] = {0, false, i + 20};
    // change colour if player chose black
    if (start) {
      gamePieces[i].colour = 0;
      gamePieces[i+1].colour = 1;
    }
    drawPiece(gamePieces[i]); 
    drawPiece(gamePieces[i + 12]);
  }
}

// draw checkers board
void drawBoard() {
  tft.fillRect(100,20,280,280, BOARD_DARK);

  // print the light tiles
  for (int i = 0; i < 8; i += 2) {
    for (int j = 0; j < 8; j += 2) {
      tft.fillRect(100 + (i*B_SQ), 20 + (j*B_SQ), B_SQ, B_SQ, BOARD_LIGHT);
      tft.fillRect(135 + (i*B_SQ), 55 + (j*B_SQ), B_SQ, B_SQ, BOARD_LIGHT);

    }
  }
  tft.println(BOARD_LIGHT);
}


void setup() {
  init();

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
  setup();
  



  while (true) {
    bool start = menuScreen();
    drawBoard();
    gameStart(start);
  }
  return 0;
}