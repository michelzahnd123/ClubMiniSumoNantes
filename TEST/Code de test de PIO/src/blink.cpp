#include <Arduino.h>

#define LED_BUILTIN 2

void blink(int temps) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(temps);
    digitalWrite(LED_BUILTIN, LOW);
    delay(temps);
}