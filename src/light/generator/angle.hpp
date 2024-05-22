#ifndef ANGLE_H
#define ANGLE_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class Angle : public AbstractGenerator {
 public:
  Angle() {
    for (int step = 0; step < STAIRS; step++) {
      int yUp = getUpperPart(stairSize[step]);
      int tUp = yUp - (step * a);
      if (start < tUp) start = tUp;

      int yDown = getLowerPart(stairSize[step]);
      int tDown = yDown - (step * a);
      if (stop > tDown) stop = tDown;
    }
    curr = stop;
  }

  bool step(CRGB *leds) {
    if (laststep > millis()) return false;

    for (int step = 0; step < STAIRS; step++) {
      int y = step * a + curr;

      int border = getUpperPart(stairSize[step]) + y;
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
      if (curr > start) direction = false;
    } else {
      curr -= 1;
      if (curr < stop) direction = true;
    }

    return true;
  }

  void settings(String setting, String value) {}

 private:
  short a = 10;
  short start = 0;
  short stop = -0;
  short curr = 0;
  unsigned long laststep = 0;
  bool direction = true;

  int getUpperPart(int leds) { return leds / 2; }
  int getLowerPart(int leds) { return (-leds / 2) + ((leds % 2) ? 0 : 1); }
};

#endif