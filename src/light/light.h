#ifndef LIGHTH
#define LIGHTH

#include <FastLED.h>

#include "pin.h"

#define PIXELS 570
CRGB leds[PIXELS];

#define STAIRS 12
short stairSize[STAIRS] = {42, 43, 43, 47, 62, 50, 47, 47, 47, 47, 47, 47};
short stairOffset[STAIRS] = {0};

#include "generator/generator.hpp"
#include "generator/nightsky.hpp"
AbstractGenerator* generator;

void initLight() {
  generator = new NightSky();

  Serial.println("Pixels: " + String(PIXELS) + " Stairs: " + String(STAIRS));

  FastLED.addLeds<WS2811, LIGHTPIN, GRB>(leds, PIXELS);
  FastLED.clear();
  FastLED.setBrightness(255);

  // init stairOffset
  int offset = 0;
  for (unsigned int i = 0; i < STAIRS; i++) {
    stairOffset[i] = offset;
    offset += stairSize[i];
  }
  FastLED.show();
}

void processLeds() {
  if (generator->step(leds)) FastLED.show();
}

#endif