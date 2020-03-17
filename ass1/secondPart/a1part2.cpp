// ---------------------------------------------------
// Names : Charles Ancheta, Poulomi Ganguly
// 
// CMPUT 275 , Winter 2020
//
// Assignment 1, Part 2: Restaurant Finder
// ---------------------------------------------------


#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <SPI.h>
#include <SD.h>

#include "jcursor.h"
#include "touchs.h"
#include "coordinates.h"


int main() {
  setup();
  btnSetup();
  while (1) {
    // Mode 0
    processTouchScreen(); // for drawing dots
    processJoystick(); // for moving cursor

    // switches to Mode 1 when joystick is pressed
    if (digitalRead(JOY_SEL) == LOW) {

      restList(); // displays list of restaurants
      
      mapInit(); // reinitializes map after exiting Mode 1
      btnSetup();
    }
  }
  Serial.end();
  return 0;
}