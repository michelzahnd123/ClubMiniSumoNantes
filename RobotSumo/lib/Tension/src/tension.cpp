#include <Arduino.h>
#include "tension.h"

// constructeur de Tension
Tension::Tension(int pin_tension){
    this->pin_tension=pin_tension;
    this->tension=false;
    this->tempsAcquisition=500;
    pinMode(this->pin_tension, INPUT);
}

// initialisation
void Tension::setPinTension(int pin_tension){
    pinMode(this->pin_tension, INPUT);
}

// entrée valeur de tension >= 2.5V
bool Tension::getEtatTension(){
    tension=digitalRead(this->pin_tension);
    delayMicroseconds(this->tempsAcquisition);
    return tension&&digitalRead(this->pin_tension);
}
