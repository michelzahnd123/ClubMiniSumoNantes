#include <Arduino.h>
#include "led.h"
#define pin_ledWork 12

Led ledWork(pin_ledWork);
int tempsAllume=50;
int tempsEteint=949;

void setup() {
  Serial.begin(115200);
  ledWork.setPinLed(pin_ledWork);
}

void loop() {
  Serial.println(" LED ");
  ledWork.on();
    delay(tempsAllume);
  ledWork.off();
    delay(tempsEteint);
}