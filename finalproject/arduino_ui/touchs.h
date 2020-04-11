// ---------------
// touchs.h
// ---------------
// Interface file for touchs.cpp
//

#ifndef _TOUCHS_H
#define _TOUCHS_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

#include "screenpos.h"

// wrap const values in namespace
namespace touch {
  // touch screen dimensions
  const uint16_t tft_height = 320;
  const uint16_t tft_width = 480;

  // touch screen pins, obtained from the documentation
  const uint8_t yp = A3;
  const uint8_t xm = A2;
  const uint8_t ym = 9;
  const uint8_t xp = 8;
  // calibration data for the touch screen, obtained from documentation
  // the minimum/maximum possible readings from the touch point
  const uint16_t ts_minx = 100;
  const uint16_t ts_miny = 120;
  const uint16_t ts_maxx = 940;
  const uint16_t ts_maxy = 920;

  // thresholds to determine if there was a touch
  const uint16_t minpr = 10;
  const uint16_t maxpr = 1000;
  
  const int16_t untch = -100; // assigned if not touched
  
  screenPos process();
  void wait(); // waits for user to touch the screen;
  void hold(); // freeze the Arduino when screen is touched
};


#endif