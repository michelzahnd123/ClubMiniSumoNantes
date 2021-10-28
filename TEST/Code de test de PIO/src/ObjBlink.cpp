#include <Arduino.h>
#include "ObjBlink.h"

BlinkObj::BlinkObj(int pinLed, int timer) {
    this->pinLed = pinLed;
    this->timer = timer;
    this->state = 0;
}


void BlinkObj::actEtat() {
    digitalWrite(this->pinLed, this->state);
    this->state != this->state;
}


int BlinkObj::getTimer() {
    return this->timer;
}

String BlinkObj::getEtat() {
    String sortie = "";
    if (this->state) {
        sortie = "on";
    } else {
        sortie = "off";
    }
    return sortie;
}

void BlinkObj::setTimer(int timer) {
    this->timer = timer;
}