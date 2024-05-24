#ifndef LIGHTH
#define LIGHTH

#include <FastLED.h>

#include "pin.h"

#define PIXELS 570
CRGB leds[PIXELS];

#define STAIRS 12
short stairSize[STAIRS] = {42, 43, 43, 47, 62, 50, 47, 47, 47, 47, 47, 47};
short stairOffset[STAIRS] = {0};

#include "generator/angle.hpp"
#include "generator/breath.hpp"
#include "generator/constant.hpp"
#include "generator/generator.hpp"
#include "generator/nightsky.hpp"
#include "generator/rotateGenerators.hpp"
#include "generator/sparkling.hpp"
#include "generator/stepByStep.hpp"
#include "generator/sweep.hpp"
#include "generator/vertical.hpp"
#include "generator/walkinglight.hpp"

AbstractGenerator* generator;
boolean status = true;

void initLight() {
  generator = new ConstantGenerator();

  Serial.println("Pixels: " + String(PIXELS) + " Stairs: " + String(STAIRS));

  FastLED.addLeds<WS2811, LIGHTPIN, GRB>(leds, PIXELS);
  FastLED.clear();
  FastLED.setBrightness(255);

  // init stairOffset
  int offset = 0;
  for (unsigned int i = 0; i < STAIRS; i++) {
    stairOffset[i] = offset;
    offset += stairSize[i];
  }
  FastLED.show();
}

void setBrightness(String val) {
  int brightness = val.toInt();
  brightness %= 255;
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void processLeds() {
  if (status) {
    if (generator->step(leds)) {
      FastLED.show();
    }
    return;
  }

  FastLED.clear();
  FastLED.show();
}

void changeGenerator(String val) {
  int genId = val.toInt();
  delete generator;

  switch (genId) {
    case 1:
      generator = new Angle();
      break;
    case 2:
      generator = new Breath();
      break;
    case 3:
      generator = new NightSky();
      break;
    case 4:
      generator = new RotateGenerators();
      break;
    case 5:
      generator = new Sparkling();
      break;
    case 6:
      generator = new StepByStep();
      break;
    case 7:
      generator = new Vertical();
      break;
    case 8:
      generator = new WalkingLight();
      break;

    default:
      generator = new ConstantGenerator();
      break;
  }
}

#endif