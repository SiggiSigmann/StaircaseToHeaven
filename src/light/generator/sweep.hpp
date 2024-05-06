#ifndef SWEEP_H
#define SWEEP_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class Sweep : public AbstractGenerator {
 public:
  bool step(CRGB *leds) {
    if (lastNewStair < millis()) {
      byte red = rVal * 51;
      byte blue = bVal * 51;
      byte green = gVal * 51;

      fill(CRGB(red, green, blue), stairOffset[nextStair], stairSize[nextStair],
           leds);

      lastNewStair = millis() + 200;
      nextStair = (nextStair + 1) % STAIRS;
    }

    for (int i = 0; i < STAIRS; i++) {
      CRGB stairColor = leds[stairOffset[i]];

      byte red = stairColor.red < rVal ? 0 : stairColor.r - rVal;
      byte blue = stairColor.blue < bVal ? 0 : stairColor.blue - bVal;
      byte green = stairColor.green < gVal ? 0 : stairColor.green - gVal;

      fill(CRGB(red, green, blue), stairOffset[i], stairSize[i], leds);
    }

    return true;
  }

  void settings(String setting, String value) {}

 private:
  unsigned long lastNewStair = 0;
  byte nextStair = 0;
  int rVal = 0;
  int bVal = 2;
  int gVal = 5;
};

#endif