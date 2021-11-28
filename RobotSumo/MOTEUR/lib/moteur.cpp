#include <Arduino.h>
#include "moteur.h"
// #include <servo.h>

// constructeur de moteur
Moteur::Moteur(int pin_moteur, Acceleration ACCEL, int vitesse_cible){
    this->pin_moteur=pin_moteur;
    this->vitesse_cible=vitesse_cible;
    pinMode(pin_moteur, OUTPUT);
    digitalWrite(pin_moteur, LOW);
}

void Moteur::setPin(int pin_moteur){
    pinMode(pin_moteur, OUTPUT);
}

void Moteur::accelerer(int pin_moteur, int vitesse_encours, int vitesse_cible){
    if(vitesse_encours<vitesse_cible){
        vitesse_encours++;
        digitalWrite(pin_moteur, vitesse_encours);
        vitesse_stable=true; // vitesse cible non atteinte
    }
    else{
        vitesse_stable=false; // vitesse stabilisée
    }
}

void Moteur::ralentir(int pin_moteur, int vitesse_encours, int vitesse_cible){
    if(vitesse_encours>vitesse_cible){
        vitesse_encours--;
        digitalWrite(pin_moteur, vitesse_encours);
        vitesse_stable=true; // vitesse cible non atteinte
    }
    else{
        vitesse_stable=false; // vitesse stabilisée
    }
}