#ifndef DIGITAL_H
#define DIGITAL_H

#include "sortie.h"

class Digital : public Sortie {
public:
    Digital(int pin);
    int getValue();
};


#endif