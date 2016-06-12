#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 150
#define BRIGHTNESS  255

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
      FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  	  Serial.begin(115200);
      FastLED.setBrightness(  BRIGHTNESS );
      leds[0] = CRGB::Red;
      FastLED.show();
      delay(500);
      // Now turn the LED off, then pause
      leds[0] = CRGB::Black;
      FastLED.show();
      delay(500);
}

void loop() { 
  
  int startChar = Serial.read();
  if (startChar == '*') {
     //debug: read one led color ( 3 bytes)
     //Serial.readBytes( (char*)(&leds[5]), 3); // read three bytes: r, g, and b.
     Serial.readBytes( (char*)leds, NUM_LEDS * 3);
     FastLED.show();
  }
  else if (startChar >= 0) {
    // discard unknown characters
  }
}
