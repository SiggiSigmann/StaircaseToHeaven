#ifndef BLACKGENERATO_H
#define BLACKGENERATO_H

#include "generator.hpp"
#include "../_util.hpp"
#include "../light.h"

class BlackGenerator : public AbstractGenerator
{
public:
 bool step(CRGB *leds) {
   if (!alreadyDone) fill(0x2aef00, 0, PIXELS, leds);
   alreadyDone = true;
   return alreadyDone;
 }

 void settings(String setting, String value) {}

private:
 bool alreadyDone = false;
};

#endif