#ifndef LED_H
#define LED_H

class Led{
private:
    int pin_led;
public:
    Led(int pin_led);
    void setPinLed(int pin_led);
    bool getPinLed();
    void on();
    void off();
    void toggle();
};

#endif