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

    //_waitForTargetInterrupt(speed);
    
    // Stops and resets the counters
    //stop(false);
    //slow();
    //block();    
    //reset();
}

void Movement::front(int speed, float length)
{
    // Forward movement of wheels
    for (int i = 0; i < _numMotors; i++)
    {
        // Start the motor
        //_motors[i].front(50+speed, length);
        _motors[i].front(speed, length);
    }
}

void Movement::back(int speed, float length)
{
    // Backward movement of wheels
    for (int i = 0; i < _numMotors; i++)
    {
        // Start the motor
        //_motors[i].back(50+speed, length);
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

    while (!(leftMotorCounter >= _motors[0].getTargetInterrupt() && rightMotorCounter >= _motors[1].getTargetInterrupt()))
    {
        // Obtem o numero de interrupts atual de cada roda
        leftMotorCounter = _motors[0].getCounter();
        rightMotorCounter = _motors[1].getCounter();     

        /*Serial.print(leftMotorCounter);
        Serial.print(":");
        Serial.println(rightMotorCounter);   

        // Passado 50ms entra
        unsigned long currentTime = millis();
        if (currentTime - lastTime >= _PERIOD)
        {
            lastTime = currentTime;

            if (leftMotorCounter > 0 && rightMotorCounter > 0)
            {
                float tickRatio = (float)(leftMotorCounter) / (float)(rightMotorCounter);

                // Deixar o esquerdo mais rapido
                if (tickRatio < 1.0)
                {
                    _motors[0].setSpeed(50+speed * tickRatio);
                }
                // Deixar o esquerdo mais lento 
                else if (tickRatio > 1.0)
                {
                    _motors[0].setSpeed(50+speed / tickRatio);
                }
            }
        }*/
    }
}