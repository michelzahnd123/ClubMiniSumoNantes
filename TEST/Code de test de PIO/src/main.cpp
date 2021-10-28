#include <Arduino.h>
#include "ObjBlink.h"

BlinkObj led1(2, 500);
BlinkObj led2(4, 1000);



void setup() {
  Serial.begin(115200);
}


void loop() {
  Serial.println(led1.getEtat());
  delay(led1.getTimer());
  led1.actEtat();
}
