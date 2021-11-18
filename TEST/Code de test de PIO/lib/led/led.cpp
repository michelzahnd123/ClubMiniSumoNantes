#include <led.h>
#include <Arduino.h>

int Led::nb = 0;

int Led::getNb() {
    return this->nb;
}

Led::Led(int pin) {
    this->nb++;
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