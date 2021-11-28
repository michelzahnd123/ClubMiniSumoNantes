#include <Arduino.h>

#ifndef COMOT_H
#define COMOT_H
#include <ESP32Servo.h>

byte ESC1pin = 32;      // signal pin for the ESC1
byte ESC2pin = 33;      // signal pin for the ESC2
byte potPinX = 19;      // analog input pin for X
byte potPinY = 21;      // analog input pin for Y
// byte BoutonPin = 3;     // joystic button

int MidValueY, MidValueX;

int MinThrottle = 1000;
int MaxThrottle = 2000;
int MidThrottleY;
int MidThrottleX;

int temp;
int i;
int potValY, potValX;
int msValX, msValY, msG, msD, deltaX;
int stepEsc = 1;

Servo ESC1;
Servo ESC2;

void initEsc();
void stopEsc();
void test1Esc();
void test2Esc();

#endif