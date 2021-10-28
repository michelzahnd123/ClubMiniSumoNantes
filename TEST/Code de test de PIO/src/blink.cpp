#include <Arduino.h>

void blink(int temps) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(temps);
    digitalWrite(LED_BUILTIN, LOW);
    delay(temps);
}