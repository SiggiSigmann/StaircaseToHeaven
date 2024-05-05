#ifndef PINSHIFT
#define PINSHIFT

#include <arduino.h>

#define PIN_SHIFT 14
#define PIN_STORE 12
#define PIN_DATA 15

#define LIGHTPIN 13

void setUpPins() {
  pinMode(PIN_SHIFT, OUTPUT);
  pinMode(PIN_STORE, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
}

#endif