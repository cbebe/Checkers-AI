#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "pieces.h"

#define SD_CS 10

// display init
MCUFRIEND_kbv tft;

#define BOARD_DARK 19458 // colours for game board
#define BOARD_LIGHT 57113 // please change i don't like
#define BOARD_SQUARE 35

struct Piece {
  uint8_t colour;
  bool king;
  uint8_t position; // position of the piece from 1 to 32
}

void drawPiece(Piece piece) {

}

void gameStart() {
  Piece white = ;
  Piece black;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {

      drawPiece() 
    }
  }
  
}

void drawBoard() {
  tft.fillRect(100,20,280,280, BOARD_DARK);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      tft.fillRect(100 + i*70, 20 + j*70, BOARD_SQUARE, BOARD_SQUARE, BOARD_LIGHT);
      tft.fillRect(135 + i*70, 55 + j*70, BOARD_SQUARE, BOARD_SQUARE, BOARD_LIGHT);

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
  
  enum {MENU, GAME_START, GAME_END} mode = MENU;

  drawBoard();
  gameStart();
  while (true) {

  }
  return 0;
}