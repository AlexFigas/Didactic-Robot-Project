#include "Expander.h"

Expander::Expander(byte address)
{
    _address = address;
    _board = Adafruit_PWMServoDriver(_address);
    _initialized = false;
}

void Expander::begin()
{
    if (!_initialized)
    {
        _board.begin();
        _initialized = true;
    }
}

void Expander::setDutyCycle(byte channel, byte duty_cycle)
{
    int pwm_on = map(duty_cycle, 0, 100, 0, 4095);
    _board.setPWM(channel, 0, pwm_on);
}