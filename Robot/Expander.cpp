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

int Expander::setDutyCycle(byte channel, float duty_cycle)
{
    int pwm_on_point = map(duty_cycle, _MIN_DUTY_CYCLE, _MAX_DUTY_CYCLE, _MIN_PWM_ON, _MAX_PWM_ON);
    _board.setPWM(channel, _PWM_OFF_POINT, pwm_on_point);
    return pwm_on_point;
}

void Expander::setPWM(byte channel, int pwm)
{
    _board.setPWM(channel, _PWM_OFF_POINT, pwm);
}