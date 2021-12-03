#ifndef MOTEUR_H
#define MOTEUR_H
class Moteur{
private:
    int pin_moteur;
    int vitesse_cible;
    int vitesse_encours;

public:
    Moteur(int pin_moteur, int vitesse_cible);
    void setPin(int pin_moteur);
    void accelerer(int vitesse_encours, int vitesse_cible);
    void ralentir(int vitesse_encours, int vitesse_cible);
};
#endif