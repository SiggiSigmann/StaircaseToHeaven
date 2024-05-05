#ifndef GENERATO_H
#define GENERATO_H

#include <Arduino.h>

class AbstractGenerator{
    public:
        virtual void step(CRGB *leds) = 0;
        virtual void settings(String setting, String value) = 0;
}; 

#endif