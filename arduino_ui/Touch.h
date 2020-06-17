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

// touch screen dimensions
#define TFT_HEIGHT 320
#define TFT_WIDTH 480
#define UNTOUCHED -100 // assigned if not touched

class Touch
{
public:
  screenPos process();
  void wait(); // waits for user to touch the screen;
  void hold(); // freeze the Arduino when screen is touched
};

#endif