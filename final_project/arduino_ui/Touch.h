// ---------------
// Touch.h
// ---------------
// Interface file for Touch.cpp
//

#ifndef _TOUCH_H
#define _TOUCH_H

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

#include "screenpos.h"

class Touch
{
public:
  // touch screen dimensions
  const uint16_t tft_height = 320;
  const uint16_t tft_width = 480;
  const int16_t untouched = -100; // assigned if not touched

  screenPos process();
  void wait(); // waits for user to touch the screen;
  void hold(); // freeze the Arduino when screen is touched
};

#endif