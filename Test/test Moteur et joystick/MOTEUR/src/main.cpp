#include <arduino.h>
#include <ESP32Servo.h>
#include "moteur.h"
#include "joystick.h"
#include "pins.h"

Moteur moteurGauche(pinMoteurGauche,0); // commande moteur en PWM
Moteur moteurDroit(pinMoteurDroit ,0 );
Joystick joystick(pinJoystickX, pinJoystickY, pinJoystickBT); //  X, Y, On

void Setup()
{
    Serial.begin(115200);
}

void Loop()
{
   // todo
   delay(1);
}