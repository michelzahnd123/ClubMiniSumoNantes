#include <Arduino.h>
#include "bouton.h"

// constructeur de Bouton
Bouton::Bouton(int pin_bouton){
    this->pin_bouton=pin_bouton;
    pinMode(pin_bouton, INPUT);
}

// initialisation
void Bouton::setPinBouton(int pin_bouton){
    pinMode(pin_bouton,INPUT);
}

// entrée valeur
bool Bouton::getEtatBouton(){
    return digitalRead(this->pin_bouton);
}