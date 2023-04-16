#include "Movement.h"

Movement::Movement(Motor *motors, float track, float wheelRadius)
{
    _motors = motors;
    _track = track;
    _wheelRadius = wheelRadius;
}

Motor *Movement::getMotors()
{
    return _motors;
}

float Movement::getTrack()
{
    return _track;
}

float Movement::getWheelRadius()
{
  return _wheelRadius;
}

void Movement::begin()
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].begin();
    }
}

void Movement::front(int speed, float length)
{
    // Forward movement of wheels
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].front(speed, length);
        delay(_DELAY_MOTORS);
    }

    // Wait for all motors to reach their target interrupts
    _waitForTargetInterrupt();

    // Stops and resets the counters
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].resetCounter();
        _motors[i].stop(true);
    }
}

void Movement::back(int speed, float length)
{
    // Backward movement of wheels
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].back(speed, length);
        delay(_DELAY_MOTORS);
    }

    // Wait for all motors to reach their target interrupts
    _waitForTargetInterrupt();

    // Stops and resets the counters
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].resetCounter();
        _motors[i].stop(true);
    }
}

void Movement::stop(bool now)
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].stop(now);
    }
}

void Movement::_waitForTargetInterrupt()
{
    bool reachedTarget = false;
    while (!reachedTarget)
    {
        for (int i = 0; i < _numMotors; i++)
        { 
            // Checks if motor has interrupt 
            if (_motors[i].hasInterrupt())
            {
                // Checks if the interrupt counter has reached the end
                if (_motors[i].getCounter() >= _motors[i].getTargetInterrupt())
                {
                    reachedTarget = true;
                    break;
                }
            }
            
        }
    }
}