#include "Expander.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Expander::Expander(uint8_t Address)
{
    // Constructor
    _ADDR = Address;
    _board = Adafruit_PWMServoDriver(_ADDR);
}

void Expander::begin()
{
    // Initialize I2C
    _board.begin();
    // _board.setPWMFreq(60);
}

void Expander::setDutyCycle(uint8_t channel, int duty_cycle)
{
    int pwm_on = map(duty_cycle, 0, 100, 0, 4095);
    _board.setPWM(channel, 4095 - pwm_on, pwm_on);
}