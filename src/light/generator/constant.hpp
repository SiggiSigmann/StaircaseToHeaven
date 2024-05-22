#ifndef BLACKGENERATO_H
#define BLACKGENERATO_H

#include "generator.hpp"
#include "../_util.hpp"
#include "../light.h"

class ConstantGenerator : public AbstractGenerator
{
public:
 bool step(CRGB *leds) {
   if (!alreadyDone) fill(0xFF00FF, 0, PIXELS, leds);
   alreadyDone = true;
   return alreadyDone;
 }

 void settings(String setting, String value) {}

private:
 bool alreadyDone = false;
};

#endif