#ifndef SORTIE_H
#define SORTIE_H

class Sortie {
protected:
    int pin;

public:
    Sortie(int pin);
    void setPin(int pin);
    virtual int getValue();
};

#endif