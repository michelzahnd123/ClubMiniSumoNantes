#include <Arduino.h>
#include "Bouton.h"

Bouton::Bouton(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
}


bool Bouton::getEtat() {
    return digitalRead(this->pin);
}
