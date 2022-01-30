#ifndef PRESENCE_H
#define PRESENCE_H

class Presence{
private:
    int pin_presence;                       // pin capteur de presence
    bool qqchoseDevant;                     // détection de quelque chose
    int tempsParasite;                      // anti-parasite 500 us
public:
    Presence(int pin_presence);
	void setPinPresence(int pin_presence);
	bool getEtatPresence();
};

#endif