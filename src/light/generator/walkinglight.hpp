#ifndef WalkingLightH
#define WalkingLightH

#include "../light.h"
#include "generator.hpp"

class WalkingLight : public AbstractGenerator {
 public:
  bool step(CRGB *leds) {
    for (int i = 0; i < PIXELS; i++) leds[i] = 0;

    if (pixel >= PIXELS - 1) pixel = -1;

    pixel++;

    leds[pixel] = CRGB(100, 24, 200);

    return true;
  }

  void settings(String setting, String value) {}
  String getSettings() { return ""; }

 private:
  int pixel = 0;
};

#endif