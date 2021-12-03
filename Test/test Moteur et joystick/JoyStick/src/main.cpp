#include <Arduino.h>
#include <ESP32Servo.h>

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(4000);

  // calibration joystic
  MidValueX = analogRead(potPinX);
  MidValueY = analogRead(potPinY);
  Serial.print(MidValueX);
  Serial.print("\t");
  Serial.println(MidValueY);
  MidThrottleY = map(MidValueY, 0, 1023, 1000, 2000);
  MidThrottleX = map(MidValueX, 0, 1023, 1000, 2000);
  initEsc();
  /*
    Serial.println("****enter to start****");
    while (Serial.available()  == 0) {
    temp = Serial.read();
    }
  */
  //test1Esc();
  test2Esc();
  delay(1000);
}

void loop() {
  potValY = analogRead(potPinY);
  potValX = analogRead(potPinX);
  msValY = map(potValY, 0, 1023, 1000, 2000); // maps pot values
  msValX = map(potValX, 0, 1023, 1300, 1700); // maps pot values
  deltaX = msValX - MidValueX - 1000;

  msG = msValY + deltaX;
  msD = msValY - deltaX;
  msD = map(msD, 1000, 2000, 2000, 1000); // inverse .. les moteurs sont tete beche

  Serial.print(deltaX);
  Serial.print("\t");
  Serial.print(msG);
  Serial.print("\t");
  Serial.println(msD);
  ESC1.writeMicroseconds(msG); // set PWM
  ESC2.writeMicroseconds(msD); // set PWM
}