#ifndef JOYSTICK_H
#define JOYSTICK_H
class Joystick{
private:
    int pin_joystickARX;                                // avant-arriere direction X
    int pin_joystickGDY;                                // gauche-droite direction Y
    int pin_joystickBouton;                             // bouton On-Off
    int valeurARX;                                      // valeur brute X
    int valeurARX_ms;                                   // valeur transformee en ms
    int valeurGDY;                                      // valeur brute Y
    int valeurGDY_ms;                                   // valeur transformee en ms
    bool etatBouton;

public:
    void setPinARX(int pin_joystickARX);
    void setPinGDY(int pin_joystickGDY);
    void setPinBouton(int pin_joystickBouton);
    Joystick(int pin_joystickARX, int pin_joystickGDY, int pin_joystickBouton);
    int getJoystickARX();
    int getJoystickGDY();
    bool getJoystickBouton();
};
#endif
