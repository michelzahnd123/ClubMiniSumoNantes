#include <Arduino.h>
#include "joystick.h"

// construction de joystick
Joystick::Joystick(int pin_joystickARX, int pin_joystickGDY, int pin_joystickBouton){
    this->pin_joystickARX=pin_joystickARX;
    this->pin_joystickGDY=pin_joystickGDY;
    this->pin_joystickBouton=pin_joystickBouton;
    pinMode(pin_joystickARX, INPUT);
    pinMode(pin_joystickGDY, INPUT);
    pinMode(pin_joystickBouton, INPUT);
}

// initialisation des entrées par Joystick
void Joystick::setPinARX(int pin_joystickARX){          // Joystick Avant - Arriere
    pinMode(this->pin_joystickARX, INTPUT);
}

void Joystick::setPinGDY(int pin_joystickGDY){          // Joystick Gauche Droite
    pinMode(this->pin_joystickGDY, INTPUT);
}

void Joystick::setPinBouton(int pin_joystickBouton){    // bouton Joystick
    pinMode(this->pin_joystickBouton, INTPUT);
}

