#include <Arduino.h>
#include <ESP32Servo.h>
#include "moteur.h"
#include "joystick.h"


Moteur moteurGauche(32);            // commande moteur en PWM
Moteur moteurDroit(33);
Joystick joystick(19,21,5);         // lecture X, Y, On


void Setup()
{
    Serial.begin(115200);
}

void Loop())
{

}