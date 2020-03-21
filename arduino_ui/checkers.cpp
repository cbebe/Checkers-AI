#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <SD.h>

#include "consts_types.h"
#include "game_states.h"

// shared variables
sharedVars shared;
// display and touch screen init
MCUFRIEND_kbv tft;

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