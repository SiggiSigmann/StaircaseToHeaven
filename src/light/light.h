#ifndef LIGHTH
#define LIGHTH

#include <FastLED.h>

#include "pin.h"

#define PIXELS 571
CRGB leds[PIXELS];

#define STAIRS 12
byte stepsize[STAIRS] = {42, 43, 43, 48, 62, 50, 47, 47, 47, 47, 47, 47};
short stepOffset[STAIRS] = {0};

#include "generator/angle.hpp"
#include "generator/generator.hpp"
AbstractGenerator* generator;

void initLight() {
  generator = new Angle();

  Serial.println("Pixels: " + String(PIXELS) + " Stairs: " + String(STAIRS));

  FastLED.addLeds<WS2813, LIGHTPIN, GRB>(leds, PIXELS);
  FastLED.clear();
  FastLED.setBrightness(100);

  // init stairOffset
  int offset = 0;
  for (unsigned int i = 0; i < STAIRS; i++) {
    stepOffset[i] = offset;
    offset += stepsize[i];
  }
  FastLED.show();
}

void processLeds() {
  if (generator->step(leds)) FastLED.show();
}

#endif