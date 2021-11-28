#include <Arduino.h>
#include "comot.h"

void initEsc()
{
  //init ESCs
Serial.println("Init ESCs");
ESC1.attach(ESC1pin, MinThrottle, MaxThrottle);
ESC2.attach(ESC2pin, MinThrottle, MaxThrottle);
delay(8000);
Serial.println("Fin init ESCs");
}

void stopEsc()
{
Serial.println("------- Stop Esc");
ESC1.writeMicroseconds(MidThrottleY);
ESC2.writeMicroseconds(MidThrottleY);
delay(10);
}

void test1Esc()
{
Serial.println("Test1 ESCs");
  //stopEsc();

Serial.println("------- sens 1 milieu vers max");
for (i = MidThrottleY; i < MaxThrottle; i += stepEsc)
{
    ESC1.writeMicroseconds(i);
    ESC2.writeMicroseconds(i);
    delay(10);
}
stopEsc();
Serial.println("------- sens 2 milieu vers min");
for (i = MidThrottleY; i > MinThrottle; i -= stepEsc)
{
    ESC1.writeMicroseconds(i);
    ESC2.writeMicroseconds(i);
    delay(10);
}
stopEsc();
Serial.println("Fin test1 ESCs");
}

void test2Esc()
{
Serial.println("Test 2 ESCs");
  //stopEsc();
  //delay (1000);
Serial.println("------- sens 1 1s");
ESC1.writeMicroseconds(1300);
ESC2.writeMicroseconds(1300);
delay(500);
stopEsc();
Serial.println("------- sens 2  1s");
ESC1.writeMicroseconds(1700);
ESC2.writeMicroseconds(1700);
delay(500);
stopEsc();
Serial.println("------- sens 1 1s");
ESC1.writeMicroseconds(1300);
ESC2.writeMicroseconds(1300);
delay(500);
stopEsc();
Serial.println("------- sens 2  1s");
ESC1.writeMicroseconds(1700);
ESC2.writeMicroseconds(1700);
delay(500);

stopEsc();
Serial.println("Fin test2 ESCs");
}