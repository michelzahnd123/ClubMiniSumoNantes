#include <Arduino.h>
#include "distance.h"

// constructeur de Distance
Distance::Distance(int pin_distance){
    this->pin_distance=pin_distance;
    this->distance=false;
    this->tempsAcquisition=500;
    pinMode(this->pin_distance, INPUT);
}

// initialisation
void Distance::setPinDistance(int pin_distance){
    pinMode(this->pin_distance, INPUT);
}

// entrée valeur 2.25V=5cm - 0.5V=50cm
bool Distance::getEtatDistance(){
    distance=digitalRead(this->pin_distance);
    delayMicroseconds(this->tempsAcquisition);
    return distance&&digitalRead(this->pin_distance);
}