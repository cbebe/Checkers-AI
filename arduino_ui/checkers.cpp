#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "game_states.h"

// shared variables
sharedVars shared;
// display and touch screen init
MCUFRIEND_kbv tft;

// returns the tile value of a board position
// use only for comparing, not for value assignment
tile board(int8_t pos) {
  // out of bounds
  if (pos < 0 || pos > 31) {return OUT;}
  return shared.board[pos];
}

// adjusts tile offsets depending on row 
void tileOS(int8_t p, int8_t *os) {
  // tile offsets {0:UL, 1:UR, 2:DL, 3:DR}
  os[0] = -4; os[2] = 4;
  os[1] = -3; os[3] = 5;
  // second row has different offsets
  if (((p % 8)/ 4)) {
    for (int8_t i = 0; i < 4; i++) {
      os[i] -= 1;
    }
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
  if (!SD.begin(c::sd_cs)) {
    while (1) {};    // Just wait, stuff exploded.
  }
}

int main() {
  // set up Arduino
  setup();
  
  while (true) {
    bool start = menuScreen();
    gameInit(start);
    game(start);
  }
  return 0;
}