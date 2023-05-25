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

void Expander::setDutyCycle(byte channel, int duty_cycle, bool digital)
{
    if (digital == false)
    {
        duty_cycle = duty_cycle > 100 ? 100 : (duty_cycle < 50 ? 50 : duty_cycle);          
    }
    
    int pwm_on_point = map(duty_cycle, _MIN_DUTY_CYCLE, _MAX_DUTY_CYCLE, _MIN_PWM_ON, _MAX_PWM_ON);
    _board.setPWM(channel, _PWM_OFF_POINT, pwm_on_point);
}