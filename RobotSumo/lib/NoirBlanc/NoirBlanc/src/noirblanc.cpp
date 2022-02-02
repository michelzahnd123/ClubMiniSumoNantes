#include <Arduino.h>
#include "noirblanc.h"

// constructeur de NoirBlanc
NoirBlanc::NoirBlanc(int pin_noirblanc){
    this->pin_noirblanc=pin_noirblanc;
    this->noirBlanc=false;
    this->tempsAcquisition=500;
    pinMode(this->pin_noirblanc, INPUT);
}

// initialisation
void NoirBlanc::setPinNoirBlanc(int pin_noirblanc){
    pinMode(this->pin_noirblanc, INPUT);
}

// entrée valeur "noir=1" ou "blanc=0"
bool NoirBlanc::getEtatNoirBlanc(){
    noirBlanc=digitalRead(this->pin_noirblanc);
    delayMicroseconds(this->tempsAcquisition);
    return noirBlanc&&digitalRead(this->pin_noirblanc);
}
