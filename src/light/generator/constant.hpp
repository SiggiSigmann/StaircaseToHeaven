#ifndef BLACKGENERATO_H
#define BLACKGENERATO_H

#include "../_util.hpp"
#include "../light.h"
#include "generator.hpp"

class ConstantGenerator : public AbstractGenerator
{
public:
 bool step(CRGB *leds) {
    fill(color, 0, PIXELS, leds);
   return true;
 }

 void settings(String setting, String value) {
   if (setting == "color") {
     color = CRGB(value.toInt());
   } else if (setting == "colorRGB") {
     byte r, g, b = 0;
     if (value.length() >= 6) {
       r = strtol(value.substring(0, 2).c_str(), NULL, 16);
       g = strtol(value.substring(2, 4).c_str(), NULL, 16);
       b = strtol(value.substring(4, 6).c_str(), NULL, 16);
       color = CRGB(r, g, b);
     }
   }
 }

 String getSettings() { return "color : color to set"; }

private:
 CRGB color = 0;
};

#endif