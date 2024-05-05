#ifndef STEPBYSTEP_H
#define STEPBYSTEP_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class StepByStep : public AbstractGenerator {
 public:
  bool step(CRGB *leds) {
    if (lastStair > millis()) return false;
    lastStair = millis() + 1000;
    nextStep = (nextStep + 1) % STAIRS;

    // reset
    if (nextStep == 0) {
      for (int j = 0; j < stepsize[STAIRS - 1]; j++) {
        int idx = j + stepOffset[STAIRS - 1];
        leds[idx] = CRGB(0, 0, 0);
      }
    } else {
      for (int j = 0; j < stepsize[nextStep - 1]; j++) {
        int idx = j + stepOffset[nextStep - 1];
        leds[idx] = CRGB(0, 0, 0);
      }
    }

    fill(CRGB(r[nextStep], g[nextStep], b[nextStep]), stepOffset[nextStep],
         stepsize[nextStep], leds);
    return true;
  }

  void settings(String setting, String value) {}

 private:
  byte r[STAIRS] = {21, 42, 63, 84, 105, 126, 147, 168, 189, 210, 231, 255};
  byte g[STAIRS] = {105, 126, 147, 168, 189, 210, 231, 255, 21, 42, 63, 84};
  byte b[STAIRS] = {189, 210, 231, 255, 21, 42, 63, 84, 105, 126, 147, 168};

  unsigned long lastStair = 0;
  byte nextStep = 0;
};

#endif