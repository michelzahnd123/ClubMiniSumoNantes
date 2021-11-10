#include <led.h>
#include <Arduino.h>

Led::Led(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Led::on() {
    digitalWrite(pin, HIGH);
}

void Led::off() {
    digitalWrite(pin, LOW);
}

void Led::toggle() {
    digitalWrite(pin, !digitalRead(pin));
}

int Led::getState() {
    return digitalRead(pin);
}

void Led::setPin(int pin) {
    pinMode(pin, OUTPUT);
}