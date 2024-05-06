#ifndef STAR_H
#define STAR_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class NightSky : public AbstractGenerator {
 public:
  bool step(CRGB *leds) {
    for (int stair = 0; stair < STAIRS; stair++) {
      short onCounter = 0;

      // dimm already on
      for (int led = 0; led < stairSize[stair]; led++) {
        int idx = led + stairOffset[stair];
        if (brignesses[idx]) {
          onCounter++;
          brignesses[idx] =
              (brignesses[idx] < cooldown) ? 0 : brignesses[idx] - cooldown;
          leds[idx] = getColor(brignesses[idx]);
        }
      }

      // create new stars
      for (int starsToBorn = shouldBeOn - onCounter; starsToBorn > 0;
           starsToBorn--) {
        if ((esp_random() % 10) > 8) continue;

        int led = esp_random() % stairSize[stair];
        int idx = led + stairOffset[stair];

        int strength = (esp_random() % 100) + 150;
        if (stair == 0) Serial.println(led + strength);
        brignesses[idx] = strength;
        leds[idx] = getColor(brignesses[idx]);
      }
    }
    return true;
  }

  void settings(String setting, String value) {}

 private:
  byte brignesses[PIXELS] = {0};
  int shouldBeOn = 8;
  byte cooldown = 1;

  CRGB getColor(byte val) { return CRGB(0, val, val / 3); }
};

#endif