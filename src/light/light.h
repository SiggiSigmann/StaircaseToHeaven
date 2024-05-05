#ifndef LIGHTH
#define LIGHTH

#include <FastLED.h>

#include "pin.h"

#define PIXELS 571
CRGB leds[PIXELS];

#define STEPS 12
int stepsize[STEPS] = {42, 43, 43, 48, 62, 50, 47, 47, 47, 47, 47, 47};
int stairOffset[STEPS] = {0};

#include "generator/breath.hpp"
#include "generator/generator.hpp"
AbstractGenerator* generator = new Breath();

void initLight() {
  FastLED.addLeds<WS2813, LIGHTPIN, GRB>(leds, PIXELS);
  FastLED.clear();
  FastLED.setBrightness(100);

  // init stairOffset
  int offset = 0;
  for (unsigned int i = 0; i < STEPS; i++) {
    stairOffset[i] = offset;
    offset += stepsize[i];
  }
  FastLED.show();
}

void processLeds() {
  if (generator->step(leds)) FastLED.show();
}

#endif