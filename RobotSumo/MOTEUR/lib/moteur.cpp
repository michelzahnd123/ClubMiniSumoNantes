#include <Arduino.h>
#include <servo.h>
#include "moteur.h"

// construction de moteur
Moteur::Moteur(int pin_moteur, int vitesse_cible){
    this->pin_moteur=pin_moteur;
    this->vitesse_cible=vitesse_cible;
    pinMode(pin_moteur, OUTPUT);
    digitalWrite(pin_moteur, LOW);
}

void Moteur::setPin(int pin_moteur){                    // moteur
    pinMode(pin_moteur, OUTPUT);
}

void Moteur::accelerer(int vitesse_encours, int vitesse_cible){
    if(vitesse_encours<vitesse_cible){                  // vitesse cible non atteinte
        vitesse_encours++;
        digitalWrite(this->pin_moteur, vitesse_encours);        
    }
}

void Moteur::ralentir(int vitesse_encours, int vitesse_cible){
    if(vitesse_encours>vitesse_cible){                  // vitesse cible non atteinte
        vitesse_encours--;
        digitalWrite(this->pin_moteur, vitesse_encours);          
    }
}