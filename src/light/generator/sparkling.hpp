#ifndef SPARKLING_H
#define SPARKLING_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class Sparkling : public AbstractGenerator {
 public:
  bool step(CRGB *leds) {
    if (laststep > millis()) return false;
    laststep = millis() + (esp_random() % 200);

    for (int i = 0; i < PIXELS; i++) {
      if (esp_random() % 50 >= 48) {
        leds[i] = CRGB::White;
      } else {
        leds[i] = CRGB::Black;
      }
    }

    return true;
  }

  void settings(String setting, String value) {}

 private:
  unsigned long laststep = 0;
};

#endif