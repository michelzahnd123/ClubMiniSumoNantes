#include <Arduino.h>
#include "Bouton.h"
#include "led.h"

Led ledRouge(2);

Bouton bouton(18);

enum Etat {
    OFF,
    ON
};

struct Test {
    int pin;
    Etat etat;
};

Etat etat = OFF;
Test test;

void setup() {
    test.pin = 13;
    test.etat = OFF;
    Serial.begin(115200);
    delay(500);
    Serial.println("hello word");
    Serial.println(ledRouge.getNb());
    Led ledVert(4);
    Serial.println(ledRouge.getNb());

}

void loop() {}

/*
void loop() {
    Serial.print(bouton.getEtat());
    if (bouton.getEtat()) {
        ledRouge.on();
    } else {
        ledRouge.off();
    }
}
*/