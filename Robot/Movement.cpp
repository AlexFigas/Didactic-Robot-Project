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

void Movement::line(int speed, float length, bool isFront)
{
    // Forward or backward direction
    if (isFront)
    {
        front(speed, length);
    }
    else 
    {
        back(speed, length);
    }

    _waitForTargetInterrupt(speed);
    
    // Stops and resets the counters
    slow();
    block();    
    reset();
}

void Movement::front(int speed, float length)
{
    // Forward movement of wheels
    for (int i = 0; i < _numMotors; i++)
    {
        // Start the motor
        _motors[i].front(speed, length);
    }
}

void Movement::back(int speed, float length)
{
    // Backward movement of wheels
    for (int i = 0; i < _numMotors; i++)
    {
        // Start the motor
        _motors[i].back(speed, length);
    }
}

void Movement::slow()
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].slow();
    }
}

void Movement::block()
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].block();
    }
}

void Movement::stop(bool now)
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[_numMotors-i-1].stop(now);
    }
}

void Movement::reset()
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].resetCounter();
    }  
}

void Movement::_waitForTargetInterrupt(int speed)
{
    // Reset the counters
    reset();

    int leftMotorCounter = 0;
    int rightMotorCounter = 0;
    
    unsigned long lastTime = 0;
    unsigned long finalTime = millis()+5000;
    
    while (!(leftMotorCounter >= _motors[0].getTargetInterrupt() && rightMotorCounter >= _motors[1].getTargetInterrupt()))
    //while ( millis()<finalTime ) 
    {
        // Obtem o numero de interrupts atual de cada roda
        leftMotorCounter = _motors[0].getCounter();
        rightMotorCounter = _motors[1].getCounter();     

        // Passado 50ms entra
        unsigned long currentTime = millis();
        if (currentTime - lastTime >= _PERIOD)
        {
            lastTime = currentTime;

            if (leftMotorCounter > 0 && rightMotorCounter > 0)
            {
                float tickRatio = (float)(leftMotorCounter) / (float)(rightMotorCounter);

                int leftSpeed = _motors[0].getSpeed();
                int rightSpeed = _motors[1].getSpeed();

                // Deixar o esquerdo mais rapido
               // Deixar o esquerdo mais rapido / direito mais lento
                if (tickRatio < 1.0)
                {
                    if (leftSpeed + 5 > _MAX_SPEED) 
                    {
                        _motors[1].setSpeed(rightSpeed - 1);
                    }
                    else
                    {
                        _motors[0].setSpeed(leftSpeed + 5);
                    }                    
                }
                // Deixar o esquerdo mais lento / direito mais rapido
                else if (tickRatio > 1.0)
                {
                    if (rightSpeed + 5 > _MAX_SPEED) 
                    {
                        _motors[0].setSpeed(leftSpeed - 1);
                    }
                    else
                    {
                        _motors[1].setSpeed(rightSpeed + 5);
                    }   
                }
            }
        }
    }
}