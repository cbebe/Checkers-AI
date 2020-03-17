
#include "touchs.h"

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

// Processes touch screen input
void processTouchScreen() {
	TSPoint touch = ts.getPoint();
	pinMode(YP, OUTPUT); 
	pinMode(XM, OUTPUT); 
	if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE) {return;}

	int16_t screen_x = map(touch.y, TS_MINX, TS_MAXX, TFT_WIDTH - 1, 0);
	int16_t screen_y = map(touch.x, TS_MINY, TS_MAXY, TFT_HEIGHT - 1, 0);
  // draw dots if map was touched
  if (screen_x > 0 && screen_x < MAP_WIDTH) {drawDots();}
  if (screen_x < TFT_WIDTH && screen_x > MAP_WIDTH) {
    if (screen_y < TFT_HEIGHT/2) {setRating();}
    else {changeSort();}
    delay(250);
  }
}