#ifndef EXPANDER_H
#define EXPANDER_H

class Expander
{
public:
    // Constructor
    Expander(uint8_t Address = 0x40);

    // Methods
    void begin();
    void setDutyCycle(uint8_t channel, int duty_cycle);

    // Variables

private:
    // Variables
    uint8_t _ADDR;
    Adafruit_PWMServoDriver _board;
};

#endif