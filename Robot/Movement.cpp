#include "Movement.h"

struct Data {
    int pwmLeft;
    int ticksLeft;
    int pwmRight;
    int ticksRight;
    float ratio;
};

static int const length = _EXEC_TIME / _PERIOD;  // Comprimento do array (20)
static Data data[length];
static int indexData;

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

void Movement::line(float speed, float length, bool isFront)
{
    reset();

    indexData = 0;
    data[indexData].pwmLeft = _motors[MOTOR_LEFT].getPWM();
    data[indexData].pwmRight = _motors[MOTOR_RIGHT].getPWM();
    data[indexData].ticksLeft = _motors[MOTOR_LEFT].getCounter();
    data[indexData].ticksRight = _motors[MOTOR_RIGHT].getCounter();
    data[indexData].ratio = 0.0f;

    // Forward or backward direction
    if (isFront)
    {
        front(speed, length);
    }
    else 
    {
        back(speed, length);
    }

    _waitForTargetInterrupt();
    
    // Stops and resets the counters
    slow();
    block();    
    reset();
}

void Movement::front(float speed, float length)
{
    // Forward movement of wheels
    for (int i = 0; i < _numMotors; i++)
    {
        // Start the motor
        _motors[i].front(speed, length);
    }
}

void Movement::back(float speed, float length)
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

void Movement::_waitForTargetInterrupt()
{    
    unsigned long timeout = millis() + _PERIOD * 4;
    unsigned long finalTime = millis() + _EXEC_TIME;

    //while (!(leftMotorCounter >= _motors[0].getTargetInterrupt() && rightMotorCounter >= _motors[1].getTargetInterrupt()))
    while ( millis()<finalTime ) 
    {
        // Passado 250ms entra
        unsigned long currentTime = millis();
        if (currentTime >= timeout)
        {
            // Obtem o numero de interrupts atual de cada roda
            int counterLeft = _motors[MOTOR_LEFT].getCounter();
            int counterRight = _motors[MOTOR_RIGHT].getCounter();

            int diffLeft = counterLeft - data[indexData].ticksLeft;
            int diffRight = counterRight - data[indexData].ticksRight;

            timeout = currentTime + _PERIOD;

            int maxDiff = max(diffLeft, diffRight);
            int minDiff = min(diffLeft, diffRight);
            float ratio = 0.0f;

            if (minDiff > 0) {

                ratio = (float)(maxDiff) / (float)(minDiff);

                if (diffLeft > diffRight) 
                {
                    _motors[MOTOR_RIGHT].setPWM(_motors[MOTOR_RIGHT].getPWM() * ratio);
                }
                else 
                {
                    _motors[MOTOR_LEFT].setPWM(_motors[MOTOR_LEFT].getPWM() * ratio);
                }
            }

            ++indexData;
            data[indexData].pwmLeft = _motors[MOTOR_LEFT].getPWM();
            data[indexData].pwmRight = _motors[MOTOR_RIGHT].getPWM();
            data[indexData].ticksLeft = counterLeft;
            data[indexData].ticksRight = counterRight;
            data[indexData].ratio = ratio;

            /*if (leftMotorCounter > 0 && rightMotorCounter > 0)
            {
                float tickRatio = (float)(leftMotorCounter) / (float)(rightMotorCounter);
                float leftSpeed = _motors[0].getSpeed();
                float rightSpeed = _motors[1].getSpeed();

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
                }*/
            }
        }

    result = "";

    char auxBuffer[80];

    sprintf( auxBuffer, "index;pwmLeft;pwmRight;ticksLeft;ticksRight;ratio\n" );
    result += String( auxBuffer );

    //Serial.println(auxBuffer);
    for (int i = 0; i < length; i++) {
      sprintf( auxBuffer, "%d;%d;%d;%d;%d;%f\n", i, data[i].pwmLeft, data[i].pwmRight, data[i].ticksLeft, data[i].ticksRight, data[i].ratio );
      //Serial.println(auxBuffer);
      result += String( auxBuffer );
    }

}