#include <Arduino.h>
#include "buzzer.h"

// constructeur de Buzzer
Buzzer::Buzzer(int pin_buzzer){
    this->pin_buzzer=pin_buzzer;
    pinMode(this->pin_buzzer, OUTPUT);
    digitalWrite(this->pin_buzzer, LOW);
}

// initialisation en sortie
void Buzzer::setPinBuzzer(int pin_buzzer){
    pinMode(this->pin_buzzer, OUTPUT);
}

// Récupération de l'état du buzzer
bool Buzzer::getPinBuzzer(){
    return digitalRead(this->pin_buzzer);
}

// Allumage ... beep !!!
void Buzzer::on(){
    digitalWrite(this->pin_buzzer, HIGH);
}

// Extinction ... silence
void Buzzer::off(){
    digitalWrite(this->pin_buzzer, LOW);
}

// Changement d'état
void Buzzer::toggle(){
    digitalWrite(this->pin_buzzer, !getPinBuzzer());
}