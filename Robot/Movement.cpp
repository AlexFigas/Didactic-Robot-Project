#include "Movement.h"
#include <BluetoothSerial.h>

extern BluetoothSerial SerialBT;

int indexData;

Data data[length];

Movement::Movement(Motor *motors, float track)
{
    _motors = motors;
    _track = track;
}

Motor *Movement::getMotors()
{
    return _motors;
}

float Movement::getTrack()
{
    return _track;
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
    float targetSpeed = speed < _MIN_SPEED ? _MIN_SPEED : (speed > _MAX_SPEED ? _MAX_SPEED : speed);

    reset();

    // Forward or backward direction
    if (isFront)
    {
        front(targetSpeed, length);
    }
    else
    {
        back(targetSpeed, length);
    }

    indexData = 0;
    data[indexData].pwmLeft = _motors[MOTOR_LEFT].getPWM();
    data[indexData].pwmRight = _motors[MOTOR_RIGHT].getPWM();
    data[indexData].ticksLeft = _motors[MOTOR_LEFT].getCounter();
    data[indexData].ticksRight = _motors[MOTOR_RIGHT].getCounter();
    data[indexData].ratio = 0.0f;

    _directionCalibration();

    // Stops and resets the counters
    slow();
    block();
    reset();

    char auxBuffer[80];
    //sprintf(auxBuffer, "index;pwmLeft;pwmRight;ticksLeft;ticksRight;ratio");
    //SerialBT.println(auxBuffer);

    for (int i = 0; i < length; i++)
    {
        sprintf(auxBuffer, "%d;%d;%d;%d;%f", data[i].pwmLeft, data[i].pwmRight, data[i].ticksLeft, data[i].ticksRight, data[i].ratio);
        SerialBT.println(auxBuffer);
    }
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

void Movement::stop()
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].stop();
    }
}

void Movement::reset()
{
    for (int i = 0; i < _numMotors; i++)
    {
        _motors[i].resetCounter();
    }
}

void Movement::_directionCalibration()
{
    unsigned long timeout = millis() + _PERIOD * _SAMPLES_TO_SKIP;
    unsigned long finalTime = millis() + _EXEC_TIME;

    int currentLeftCounter = _motors[MOTOR_LEFT].getCounter();
    int currentRightCounter = _motors[MOTOR_RIGHT].getCounter();

    int leftTarget = _motors[MOTOR_LEFT].getTargetInterrupt();
    int rightTarget = _motors[MOTOR_RIGHT].getTargetInterrupt();

    while ( (currentLeftCounter < leftTarget || currentRightCounter < rightTarget ) )
    {
        // Passado PERIOD entra
        unsigned long currentTime = millis();
        if (currentTime >= timeout)
        {
            // Obtem o numero de interrupts atual de cada roda
            currentLeftCounter = _motors[MOTOR_LEFT].getCounter();
            currentRightCounter = _motors[MOTOR_RIGHT].getCounter();

            int diffLeft = currentLeftCounter - data[indexData].ticksLeft;
            int diffRight = currentRightCounter - data[indexData].ticksRight;

            timeout = currentTime + _PERIOD;

            int maxDiff = max(diffLeft, diffRight);
            int minDiff = min(diffLeft, diffRight);
            float ratio = 0.0f;

            float motorDif;
            float rightSpeed, leftSpeed;

            if (minDiff > 0)
            {
                ratio = (float)(maxDiff) / (float)(minDiff);
                float ratioAux = (ratio - 1.0) / 2.0;
                float ratioAdd = 1.0 + ratioAux;
                float ratioSub = 1.0 - ratioAux;

                if (diffLeft > diffRight)
                {
                    rightSpeed = _motors[MOTOR_RIGHT].getPWM() * ratioAdd;
                    leftSpeed = _motors[MOTOR_LEFT].getPWM() * ratioSub;
                }
                else
                {
                    rightSpeed = _motors[MOTOR_RIGHT].getPWM() * ratioSub;
                    leftSpeed = _motors[MOTOR_LEFT].getPWM() * ratioAdd;
                }

                float motorDif_right = rightSpeed < _MIN_PWM ? _MIN_PWM - rightSpeed : (rightSpeed > _MAX_PWM ? _MAX_PWM-rightSpeed : 0);
                float motorDif_left = leftSpeed < _MIN_PWM ? _MIN_PWM - leftSpeed : (leftSpeed > _MAX_PWM ? _MAX_PWM-leftSpeed : 0);

                rightSpeed = rightSpeed+motorDif_left < _MIN_PWM ? _MIN_PWM : (rightSpeed+motorDif_left > _MAX_PWM ? _MAX_PWM : rightSpeed+motorDif_left);
                leftSpeed = leftSpeed+motorDif_right < _MIN_PWM ? _MIN_PWM : (leftSpeed+motorDif_right > _MAX_PWM ? _MAX_PWM : leftSpeed+motorDif_right);
                
                _motors[MOTOR_RIGHT].setPWM(rightSpeed);
                _motors[MOTOR_LEFT].setPWM(leftSpeed);

                ++indexData;
                data[indexData].pwmLeft = _motors[MOTOR_LEFT].getPWM();
                data[indexData].pwmRight = _motors[MOTOR_RIGHT].getPWM();
                data[indexData].ticksLeft = currentLeftCounter;
                data[indexData].ticksRight = currentRightCounter;
                data[indexData].ratio = ratio;
            }
        }
    }
}
