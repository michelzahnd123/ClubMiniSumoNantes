#include <Arduino.h>
#include "presence.h"

// constructeur de Presence
Presence::Presence(int pin_presence){
	this->pin_presence=pin_presence;
	this->qqchoseDevant=false;
	this->tempsParasite=500;
	pinMode(this->pin_presence, INPUT);
	}

// initialisation
void Presence::setPinPresence(int pin_presence){
	pinMode(this->pin_presence, INPUT);
	}

// entree valeur
bool Presence::getEtatPresence(){
	qqchoseDevant=digitalRead(this->pin_presence);
	delayMicroseconds(this->tempsParasite);
	return qqchoseDevant&&digitalRead(this->pin_presence);
	}
