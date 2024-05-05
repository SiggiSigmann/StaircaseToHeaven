#ifndef BREATH_H
#define BREATH_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class Breath : public AbstractGenerator {
 public:
  bool step(CRGB *leds) {
    if (direction)
      brightness++;
    else
      brightness--;

    if (brightness == 255) direction = false;
    if (brightness == 0) direction = true;

    fill(CRGB(brightness, 1, 1), 0, PIXELS, leds);
    return true;
  }

  void settings(String setting, String value) {}

 private:
  int brightness = 0;
  uint8_t direction = true;
};

#endif