#ifndef TENSION_H
#define TENSION_H

class Tension{
private:
    int pin_tension;                    // prise de tension
    bool tension;                       // tension existante
    int tempsAcquisition;               // double entrée
public:
    Tension(int pin_tension);
    void setPinTension(int pin_tension);
    bool getEtatTension();
};

#endif