#ifndef DISTANCE.H
#define DISTANCE_H

class Distance{
private:
    int pin_distance;               // pin d'entrée
    bool distance;                  // distance <= 40cm
    int tempsAcquisition;           // double mesure
public:
    Distance(int pin_distance);
    void setPinDistance(int pin_distance);
    bool getEtatDistance();
};

#endif