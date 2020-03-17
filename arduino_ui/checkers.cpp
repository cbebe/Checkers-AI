#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "pieces.h"

#define SD_CS 10

// display init
MCUFRIEND_kbv tft;


void drawBoard() {
  tft.fillRect(0,0)
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
  while (true) {

  }
  return 0;
}