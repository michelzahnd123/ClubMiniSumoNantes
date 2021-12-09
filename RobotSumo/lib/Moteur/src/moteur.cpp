#include <Arduino.h>
#include "moteur.h"
// #include <servo.h>

// constructeur de moteur
Moteur::Moteur(int pin_moteur) {
    this->pin_moteur = pin_moteur;
    pinMode(pin_moteur, OUTPUT);
    digitalWrite(pin_moteur, LOW);
}

int Moteur::accelerer(int vitesse_cible) {
    if (vitesse_encours != vitesse_cible) {
        if (vitesse_encours < vitesse_cible) {
            vitesse_encours++;
        } else {
            vitesse_encours--;
        }
        digitalWrite(pin_moteur, vitesse_encours);
    }
    return vitesse_encours;
}