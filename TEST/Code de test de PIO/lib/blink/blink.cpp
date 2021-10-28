#include <Arduino.h>

#define LED_BUILTIN 2

void blink(bool state) {
    digitalWrite(LED_BUILTIN, state);
}

bool inversion(bool state, String& etat) {
    if (state) {
        etat = "allumé";
    } else {
        etat = "eteint";
    }
    return !state;
}