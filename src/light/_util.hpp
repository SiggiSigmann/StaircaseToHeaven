#ifndef FASTLEDUTIL_H
#define FASTLEDUTIL_H

#include <Arduino.h>
#include "light.h"

CRGB combineColor(CRGB c1, CRGB c2)
{
    uint8_t r = (c1.red + c2.red) >> 1;
    uint8_t g = (c1.green + c2.green) >> 1;
    uint8_t b = (c1.blue + c2.blue) >> 1;
    return CRGB(r, g, b);
}

CRGB maxColor(CRGB c1, CRGB c2)
{
    uint8_t r = max(c1.red, c2.red);
    uint8_t g = max(c1.green, c2.green);
    uint8_t b = max(c1.blue, c2.blue);
    return CRGB(r, g, b);
}

void fill(CRGB color, int start, int size, CRGB *leds) {
  int end = start + size;
  if (end >= PIXELS) end = PIXELS;

  for (int i = start; i < end; i++) {
    CRGB combined = combineColor(leds[i], CRGB(color));
    leds[i] = combined;
  }
}

void fill(uint32_t color, int start, int size, CRGB *leds) {
  int end = start + size;
  if (end >= PIXELS) end = PIXELS;
  for (int i = start; i < end; i++) {
    CRGB combined = combineColor(leds[i], CRGB(color));
    leds[i] = combined;
  }
}

void combine(uint32_t color, int start, int size, CRGB *leds)
{
    int end = start + size;
    if (end >= PIXELS)
        end = PIXELS;
    for (int i = start; i < end; i++)
    {
        CRGB combined = maxColor(leds[i], CRGB(color));
        leds[i] = combined;
    }
}

int getMax(short arr[], int size) {
  if (size == 0) {
    // Return some default value if the array is empty
    return 0;
  }

  int max = arr[0];
  for (size_t i = 1; i < size; ++i) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

#endif