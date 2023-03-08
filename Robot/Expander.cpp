#include "Expander.h"

Expander::Expander(byte address)
{
    // Constructor
    _ADDR = address;
    _board = Adafruit_PWMServoDriver(_ADDR);
}

void Expander::begin()
{
    // Initialize I2C
    _board.begin();
}

void Expander::setDutyCycle(byte channel, byte duty_cycle)
{
    int pwm_on = map(duty_cycle, 0, 100, 0, 4095);
    _board.setPWM(channel, 0, pwm_on);
}