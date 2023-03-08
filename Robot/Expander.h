#ifndef EXPANDER_H
#define EXPANDER_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

class Expander
{
public:
    // Constructor
    Expander(byte address = 0x40);

    // Methods
    void begin();
    void setDutyCycle(byte channel, byte duty_cycle);

    // Variables

private:
    // Variables
    byte _ADDR;
    Adafruit_PWMServoDriver _board;
};

#endif