# include <Arduino.h>
# include "led.h"

// Constructeur de LED
Led::Led(int pin_led){
    this->pin_led=pin_led;
    pinMode(this->pin_led, OUTPUT);
    digitalWrite(this->pin_led, LOW);
}

// Initialisation en sortie
void Led::setPinLed(int pin_led){
    pinMode(this->pin_led, OUTPUT);
}

// Récupération de l'état de la LED
bool Led::getPinLed(){
    return digitalRead(this->pin_led);
}

// Allumage
void Led::on(){
    digitalWrite(this->pin_led, HIGH);
}

// Extinction
void Led::off(){
    digitalWrite(this->pin_led, LOW);
}

// Changement d'état
void Led::toggle(){
    digitalWrite(this->pin_led, !getPinLed());
}
