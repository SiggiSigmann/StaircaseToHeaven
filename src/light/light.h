#ifndef LIGHTH
#define LIGHTH

#include <FastLED.h>

#include "pin.h"

#define PIXELS 571
CRGB leds[PIXELS];

#define STAIRS 12
byte stairSize[STAIRS] = {42, 43, 43, 48, 62, 50, 47, 47, 47, 47, 47, 47};
short stairOffset[STAIRS] = {0};

#include "generator/generator.hpp"
#include "generator/rotateGenerators.hpp"
AbstractGenerator* generator;

void initLight() {
  generator = new RotateGenerators();

  Serial.println("Pixels: " + String(PIXELS) + " Stairs: " + String(STAIRS));

  FastLED.addLeds<WS2811, LIGHTPIN, GRB>(leds, PIXELS);
  FastLED.clear();
  FastLED.setBrightness(150);

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