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

// lecture & transformation des valeurs du joystick
int Joystick::getJoystickARX();{                        // valeur entre 0 et 1023
    valeurARX=analogRead(this->pin_joystickARX);
    valeurARX_ms=map(valeurARX, 0,1023, 1000, 2000);    // entre 1000 et 2000
    if(valeurARX_ms>1450 and valeurARX_ms<1550){valeurARX_ms=1500;}
    return valeurARX_ms;
}

int Joystick::getJoystickGDY();{                        // valeur entre 0 et 1023
    valeurGDY=analogRead(this->pin_joystickGDY);
    valeurGDY_ms=map(valeurGDY, 0,1023, 1000, 2000);    // entre 1000 et 2000
    if(valeurGDY_ms>1450 and valeurGDY_ms<1550){valeurGDY_ms=1500;}
    return valeurGDY_ms;
}

bool Joystick::getJoystickBouton();{                     // booleen On - Off
    return digitalRead(this->pin_joystickBouton)=etatBouton;
}
