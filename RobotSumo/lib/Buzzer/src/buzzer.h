#ifndef BUZZER_H
#define BUZZER_H

class Buzzer{
private:
    int pin_buzzer;
public:
    Buzzer(int pin_buzzer);
    void setPinBuzzer(int pin_buzzer);
    bool getPinBuzzer();
    void on();
    void off();
    void toggle();
};

#endif