#ifndef BOUTON_H
#define BOUTON_H

class Bouton{
private:
    int pin_bouton;                   // pin d'entrée
    bool appuiBouton;                 // saisie de l'état bouton
    int tempsAcquisition;             // anti-rebond 500 us
public:
    Bouton(int pin_bouton);
    void setPinBouton(int pin_bouton);
    bool getEtatBouton();
};

#endif