#ifndef BOUTON_H
#define BOUTON_H

//class qui représente un couton
class Bouton {
private:
    int pin;
public:
    Bouton(int pin);
    bool getEtat();
};


#endif