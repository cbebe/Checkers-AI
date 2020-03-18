/*
	Just a simple example of how to use the touch screen.
	The coordinates that were touched are displayed on the screen.
*/

#include <Arduino.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>

#define SD_CS 10

// touch screen pins, obtained from the documentaion
#define YP A3 // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 9  // can be a digital pin
#define XP 8  // can be a digital pin

// width/height of the display when rotated horizontally
#define TFT_WIDTH  480
#define TFT_HEIGHT 320

// calibration data for the touch screen, obtained from documentation
// the minimum/maximum possible readings from the touch point
#define TS_MINX 100
#define TS_MINY 110
#define TS_MAXX 960
#define TS_MAXY 910

// thresholds to determine if there was a touch
#define MINPRESSURE   10
#define MAXPRESSURE 1000

MCUFRIEND_kbv tft;

// a multimeter reading says there are 300 ohms of resistance across the plate,
// so initialize with this to get more accurate readings
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup() {
	init();

	// do not actually need to change the pinmode of the digital TouchScreen
	// pins, the function to get a touchscreen reading will set and change them

	Serial.begin(9600);

	uint16_t ID = tft.readID();
	tft.begin(ID);

	tft.fillScreen(TFT_BLACK);
	tft.setRotation(1);

	tft.setTextSize(2);
	tft.println("Waiting for touch");
}

void processTouchScreen() {
	TSPoint touch = ts.getPoint();

	// restore pinMode to output after reading the touch
    // this is necessary to talk to tft display
	pinMode(YP, OUTPUT); 
	pinMode(XM, OUTPUT); 

	if (touch.z < MINPRESSURE || touch.z > MAXPRESSURE) {
		return;
	}

	int16_t screen_x = map(touch.y, TS_MINX, TS_MAXX, TFT_WIDTH-1, 0);
	int16_t screen_y = map(touch.x, TS_MINY, TS_MAXY, TFT_HEIGHT-1, 0);

	Serial.print(screen_x);
	Serial.print(' ');
	Serial.print(screen_y);
	Serial.print(' ');
	Serial.println(touch.z);

	// this won't work if you do not reset pin modes
	tft.fillRect(TFT_WIDTH/2, TFT_HEIGHT/2, 200, 100, TFT_BLACK);
	tft.setCursor(TFT_WIDTH/2,TFT_HEIGHT/2);
    tft.setTextSize(2);
    tft.print(screen_x); tft.print(" "); tft.println(screen_y);

	delay(200);
}


int main() {
	setup();

	while (true) {
		processTouchScreen();
	}

	Serial.end();

	return 0;
}
