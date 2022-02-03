#ifndef ACCELERO_H
#define ACCELERO_H

class Accelero{
private:
    int pin_accelero;                   // pin INT
    bool accelero;                      // int ?
    int tempsAcquisition;               // double test
public:
    Accelero(int pin_accelero);
    void setPinAccelero(int pin_accelero);
    bool getEtatAccelero();
};

#endif 