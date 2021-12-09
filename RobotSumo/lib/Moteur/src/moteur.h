#ifndef MOTEUR_H
#define MOTEUR_H

class Moteur {
private:
    int pin_moteur;
    int vitesse_cible;
    int vitesse_encours;
public:
    Moteur(int pin_moteur);
    int accelerer(int vitesse_cible);
};

#endif