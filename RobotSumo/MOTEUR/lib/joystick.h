#ifndef JOYSTICK_H
#define JOYSTICK_H

class Joystick{
private:
    int pin_joystickARX;
    int pin_joystickGDY;
    int pin_joystickBouton;
public:
    setPinARX(int pin_joystickARX);
    setPinGDY(int pin_joystickGDY);
    setPinBouton(int pin_joystickBouton);

};
#endif
