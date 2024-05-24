#ifndef GENERATO_H
#define GENERATO_H

#include <Arduino.h>

class AbstractGenerator{
    public:
        virtual bool step(CRGB *leds) = 0;
        virtual void settings(String setting, String value) = 0;
        virtual String getSettings();
}; 

#endif