#include "Movement.h"

Movement::Movement(Motor *motors, int wheelbase)
{
    _motors = motors;
    _wheelbase = wheelbase;
}

Motor *Movement::getMotors()
{
    return _motors;
}

int Movement::getWheelbase()
{
    return _wheelbase;
}

void Movement::begin()
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].begin();
    }
}

void Movement::front(int speed)
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].front(speed);
    }
}

void Movement::back(int speed)
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].setSpeed(speed);
        _motors[i].back(speed);
    }
}

void Movement::stop(bool now)
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].stop(now);
    }
}
