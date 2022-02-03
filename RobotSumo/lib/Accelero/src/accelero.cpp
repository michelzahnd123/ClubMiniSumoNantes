#include <Arduino.h>
#include "accelero.h"

// constructeur de Accelero
Accelero::Accelero(int pin_accelero){
    this->pin_accelero=pin_accelero;
    this->accelero=false;
    this->tempsAcquisition=500;
    pinMode(this->pin_accelero, INPUT);
}

// initialisation
void Accelero::setPinAccelero(int pin_accelero){
    pinMode(this->pin_accelero, INPUT);
}

// entrée valeur INT
bool Accelero::getEtatAccelero(){
    accelero=digitalRead(this->pin_accelero);
    delayMicroseconds(this->tempsAcquisition);
    return accelero&&digitalRead(this->pin_accelero);
}
