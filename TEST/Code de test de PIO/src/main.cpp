#include <Arduino.h>
#include "Bouton.h"
#include "led.h"

Led ledRouge(2);
Bouton bouton(18);


void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.print("hello word");
}


void loop() {
    Serial.print(bouton.getEtat());
    if (bouton.getEtat()) {
        ledRouge.on();
    } else {
        ledRouge.off();
    }
}
