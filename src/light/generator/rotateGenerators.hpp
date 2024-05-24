#ifndef ROTATEGENERATOR_H
#define ROTATEGENERATOR_H

#include "../_util.hpp"
#include "../light.h"
#include "angle.hpp"
#include "breath.hpp"
#include "nightsky.hpp"
#include "sparkling.hpp"
#include "stepByStep.hpp"
#include "sweep.hpp"
#include "vertical.hpp"
#include "walkinglight.hpp"

class RotateGenerators : public AbstractGenerator {
 public:
  bool step(CRGB* leds) {
    if (lastChange < millis()) {
      lastChange = millis() + 60000;
      delete generator;

      switch (nextGenerator) {
        case 1:
          generator = new Breath();
          break;
        case 2:
          generator = new Sparkling();
          break;
        case 3:
          generator = new NightSky();
          break;
        case 4:
          generator = new StepByStep();
          break;
        case 5:
          generator = new Sweep();
          break;
        case 6:
          generator = new Vertical();
          break;
        case 7:
          generator = new WalkingLight();
          break;

        default:
          generator = new Angle();
          break;
      }

      nextGenerator = (nextGenerator + 1) % 8;
    }

    return generator->step(leds);
  }

  void settings(String setting, String value) {}
  String getSettings() { return ""; }

 private:
  unsigned long lastChange = 0;
  int nextGenerator = 0;
  AbstractGenerator* generator = new Angle();
};

#endif