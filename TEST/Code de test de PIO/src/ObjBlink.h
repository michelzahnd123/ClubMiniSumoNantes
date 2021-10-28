#ifndef OBJBLINK_H
#define OBJBLINK_H

#include <Arduino.h>

class BlinkObj {

private:
    int pinLed;
    int timer;
    int state;
public:
    BlinkObj(int PinLed, int timer);
    BlinkObj(int PinLed)

        void actEtat();
    int getTimer();
    String getEtat();
    void setTimer(int timer);


};


#endif