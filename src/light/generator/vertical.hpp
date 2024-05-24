#ifndef VERTICAL_H
#define VERTICAL_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class Vertical : public AbstractGenerator {
 public:
  bool step(CRGB *leds) {
    if (laststep > millis()) return false;

    for (int step = 0; step < STAIRS; step++) {
      int border = (stairSize[step] / 2) + curr;
      border = (border > 0) ? border : 0;

      for (int ledInStep = 0; ledInStep < stairSize[step]; ledInStep++) {
        short idx = stairOffset[step] + ledInStep;
        if (ledInStep < border) {
          leds[idx] = CRGB(0, 0, 0);
        } else {
          leds[idx] = CRGB(100, 50, 75);
        }
      }
    }

    laststep = millis() + 100;
    if (direction) {
      curr += 1;
      if (curr >= start) direction = false;
    } else {
      curr -= 1;
      if (curr <= stop) direction = true;
    }

    return true;
  }

  void settings(String setting, String value) {}
  String getSettings() { return ""; }

 private:
  short maxLength = getMax(stairSize, STAIRS);
  short start = maxLength - (maxLength / 2);
  short stop = (maxLength / 2) - maxLength;
  short curr = start;
  unsigned long laststep = 0;
  bool direction = true;
};

#endif