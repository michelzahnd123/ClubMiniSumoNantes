#include <Arduino.h>
#include "blink.h"

#define LED_BUILTIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

bool state = 0;
String etat = "";

void loop() {
  blink(state);
  state = inversion(state, etat);
  Serial.println(etat);
  delay(1000);
}
