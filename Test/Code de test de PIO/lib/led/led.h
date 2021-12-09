#ifndef LED_H
#define LED_H

//class qui represente une led
class Led {
private:
    int pin;
    static int nb;
public:
    Led(int pin);
    void on();
    void off();
    void toggle();
    int getState();
    void setPin(int pin);
    int getNb();
};


#endif