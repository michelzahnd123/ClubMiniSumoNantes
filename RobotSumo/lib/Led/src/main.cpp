#include <Arduino.h>
#include "led.h"

Led ledRouge(2);
Led ledVerte(4);
Led ledBlanche(16);
Led ledBleue(17);

int tempsPause=125;

void setup() {
  Serial.begin(115200);
  ledRouge.setPinLed(2);
  ledVerte.setPinLed(4);
  ledBlanche.setPinLed(16);
  ledBleue.setPinLed(17);
}

void loop() {
  ledRouge.on();
    delay(tempsPause);
  ledRouge.off();
  ledVerte.on();
    delay(tempsPause);
  ledVerte.off();
  ledBlanche.on();
    delay(tempsPause);
  ledBlanche.off();
  ledBleue.on();
    delay(tempsPause);
  ledBleue.off();
}