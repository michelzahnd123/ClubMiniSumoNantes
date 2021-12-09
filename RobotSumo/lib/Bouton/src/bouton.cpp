#include <Arduino.h>
#include "bouton.h"

// constructeur de Bouton
Bouton::Bouton(int pin_bouton){
    this->pin_bouton=pin_bouton;
    this->appuiBouton=false;
    this->tempsAcquisition=500;
    pinMode(pin_bouton, INPUT);
}

// initialisation
void Bouton::setPinBouton(int pin_bouton){
    pinMode(this->pin_bouton,INPUT);
}

// entrée valeur sans rebond
bool Bouton::getEtatBouton(){
    appuiBouton=digitalRead(this->pin_bouton);
    delayMicroseconds(tempsAcquisition);
    return appuiBouton&&digitalRead(this->pin_bouton);
}
