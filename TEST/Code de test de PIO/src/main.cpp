#include <Arduino.h>
#include "blink.h"

#define LED_BUILTIN 2

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}



void loop() {
  blink(1000);
}
