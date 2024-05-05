#ifndef VERTICAL_H
#define VERTICAL_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class Vertical : public AbstractGenerator {
 public:
  bool step(CRGB *leds) {
    for (int step = 0; step < STAIRS; step++) {
      int line = (stepsize[step] / 2) + curr;
      line = (line > 0) ? line : 0;

      for (int ledInStep = 0; ledInStep < stepsize[step]; ledInStep++) {
        short idx = stepOffset[step] + ledInStep;
        if (ledInStep < line) {
          leds[idx] = CRGB(0, 0, 0);
        } else {
          leds[idx] = CRGB(100, 50, 75);
        }
      }
    }

    if (laststep < millis()) {
      laststep = millis() + 100;
      if (direction) {
        curr += 1;
        if (curr >= start) direction = false;
      } else {
        curr -= 1;
        if (curr <= stop) direction = true;
      }
    }

    return true;
  }

  void settings(String setting, String value) {}

 private:
  short maxLength = getMax(stepsize, STAIRS);
  short start = maxLength - (maxLength / 2);
  short stop = (maxLength / 2) - maxLength;
  short curr = start;
  unsigned long laststep = 0;
  bool direction = true;
};

#endif