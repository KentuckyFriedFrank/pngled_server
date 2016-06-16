#define USE_OCTOWS2811
#include<OctoWS2811.h>
#include<FastLED.h>

#define NUM_LEDS_PER_STRIP 72
#define NUM_STRIPS 8
#define NUM_LEDS (NUM_STRIPS * NUM_LEDS_PER_STRIP)
CRGB leds[NUM_LEDS];

#define BRIGHTNESS  128

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

void setup() {
  Serial.begin(115200);
  //FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP);
  FastLED.setBrightness(  BRIGHTNESS );
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Green;
  leds[2] = CRGB::Blue;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  leds[1] = CRGB::Black;
  leds[2] = CRGB::Black;
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
