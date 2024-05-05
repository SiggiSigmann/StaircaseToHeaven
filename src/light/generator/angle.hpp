#ifndef ANGLE_H
#define ANGLE_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class Angle : public AbstractGenerator {
 public:
  Angle() {
    short maxIdx = 0, maxY=0;
    for (int step = 1; step < STAIRS; step++) {
      int y = (stepsize[step] / 2) - b - (a * step);
      if(maxY < y){
        maxY = y;
        maxIdx = step;
      }
    }
    start = maxY;

    for (int step = 1; step < STAIRS; step++) {
      int y = (-stepsize[step] / 2) - b - (a * step);
      if (maxY > y) {
        maxY = y;
        maxIdx = step;
      }
    }
    stop = maxY-1;
    curr = stop;
    Serial.println(String(start) + " " + String(stop));
  }

  bool step(CRGB *leds) {
    if (laststep > millis()) return false;

    for (int step = 0; step < STAIRS; step++) {
      int y = step * a + curr + b;

      int border = (stepsize[step] / 2) + y;
      border = (border > 0) ? border : 0;

      for (int ledInStep = 0; ledInStep < stepsize[step]; ledInStep++) {
        short idx = stepOffset[step] + ledInStep;
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

 private:
  short a = 5, b = 0;
  short maxLength = getMax(stepsize, STAIRS);
  short start = 20;
  short stop = -20;
  short curr = start;
  unsigned long laststep = 0;
  bool direction = true;
};

#endif