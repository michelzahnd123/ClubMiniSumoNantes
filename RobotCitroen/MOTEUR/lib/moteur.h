#ifndef MOTEUR_H
#define MOTEUR_H

enum Acceleration {ACCEL, DECEL, STABL};

class Moteur{
private:
    int pin_moteur;
    int vitesse_cible;
public:
    int vitesse_encours;
    Moteur(int pin_moteur, Acceleration mouvement, int vitesse_cible);
    void setPin(int pin_moteur);
    void accelerer(int pin_moteur, int vitesse_encours, int vitesse_cible);
    void ralentir(int pin_moteur, int vitesse_encours, int vitesse_cible);
    bool vitesse_stable;
};

#endif