#include "MovementTwoMotors.h"

#include <BluetoothSerial.h>
extern BluetoothSerial SerialBT;

int indexDataCurve;

Data dataCurve[length];

MovementTwoMotors::MovementTwoMotors(Motor *motors, float track, float wheelRadius) : Movement(motors, track, wheelRadius)
{
    _numMotors = 2;
}

void MovementTwoMotors::curve(float speed, int radius, int angle, bool isLeft)
{
    reset();

    if (isLeft == true)
    {
        left(speed, radius, angle);
    }
    else
    {
        right(speed, radius, angle);
    }
    
    indexDataCurve = 0;
    dataCurve[indexDataCurve].pwmLeft = _motors[MOTOR_LEFT].getPWM();
    dataCurve[indexDataCurve].pwmRight = _motors[MOTOR_RIGHT].getPWM();
    dataCurve[indexDataCurve].ticksLeft = _motors[MOTOR_LEFT].getCounter();
    dataCurve[indexDataCurve].ticksRight = _motors[MOTOR_RIGHT].getCounter();
    dataCurve[indexDataCurve].ratio = 0.0f;

    _waitForTarget();

    // Stops and resets the counters
    slow();
    block();
    reset();

    char auxBuffer[80];

    sprintf(auxBuffer, "index;pwmLeft;pwmRight;ticksLeft;ticksRight;ratio");
    SerialBT.print(auxBuffer);

    // Serial.println(auxBuffer);
    for (int i = 0; i < length; i++)
    {
        sprintf(auxBuffer, "%d;%d;%d;%d;%d;%f", i, dataCurve[i].pwmLeft, dataCurve[i].pwmRight, dataCurve[i].ticksLeft, dataCurve[i].ticksRight, dataCurve[i].ratio);
        SerialBT.print(auxBuffer);
    }
}

void MovementTwoMotors::left(float speed, int radius, int angle)
{
    if (radius == 0)
    {
        // TODO
    }
    else
    {
        float leftSpeed = (((float)(radius) - (getTrack() / 2.0)) / (float)(radius)) * speed;
        float rightSpeed = (((float)(radius) + (getTrack() / 2.0)) / (float)(radius)) * speed;

        // Activate motors
        SerialBT.println(leftSpeed);
        SerialBT.println(rightSpeed);

        getMotors()[0].front(leftSpeed, 1.0);
        getMotors()[1].front(rightSpeed, 1.0);
    }
}

void MovementTwoMotors::right(float speed, int radius, int angle)
{
    if (radius == 0)
    {
        // TODO
    }
    else
    {
        float leftSpeed = (((float)(radius) + (getTrack() / 2.0)) / (float)(radius)) * speed;
        float rightSpeed = (((float)(radius) - (getTrack() / 2.0)) / (float)(radius)) * speed;

        // Activate motors
        SerialBT.println(leftSpeed);
        SerialBT.println(rightSpeed);

        // Activate motors
        getMotors()[0].front(leftSpeed, 1.0);
        getMotors()[1].front(rightSpeed, 1.0);
    }
}

void MovementTwoMotors::_waitForTarget()
{
    unsigned long timeout = millis() + _PERIOD * _SAMPLES_TO_SKIP;
    unsigned long finalTime = millis() + _EXEC_TIME;

    //while (!(leftMotorCounter >= _motors[0].getTargetInterrupt() !! rightMotorCounter >= _motors[1].getTargetInterrupt()))
    while (millis() < finalTime)
    {
        unsigned long currentTime = millis();
        if (currentTime >= timeout)
        {
            // Obtem o numero de interrupts atual de cada roda
            int counterLeft = _motors[MOTOR_LEFT].getCounter();
            int counterRight = _motors[MOTOR_RIGHT].getCounter();

            int diffLeft = counterLeft - dataCurve[indexDataCurve].ticksLeft;
            int diffRight = counterRight - dataCurve[indexDataCurve].ticksRight;

            float ratio = 0.0f;

            timeout = currentTime + _PERIOD;

            ++indexDataCurve;
            dataCurve[indexDataCurve].pwmLeft = _motors[MOTOR_LEFT].getPWM();
            dataCurve[indexDataCurve].pwmRight = _motors[MOTOR_RIGHT].getPWM();
            dataCurve[indexDataCurve].ticksLeft = counterLeft;
            dataCurve[indexDataCurve].ticksRight = counterRight;
            dataCurve[indexDataCurve].ratio = ratio;
        }
    }
}

/*
// Distance and time it takes the center of the robot to reach
float distance = (2 * M_PI * radius * angle) / 360;
float time = distance / speed;

// Maximum speed for each motor
float maxSpeed = 100; // adjust as needed

// Speed ​​calculation for the left motor
float leftDistance = (2 * M_PI * (radius - (_wheelbase / 2)) * angle) / 360;
float leftSpeed = (leftDistance / time) / maxSpeed * speed;

// Speed ​​calculation for the right motor
float rightDistance = (2 * M_PI * (radius + (_wheelbase / 2)) * angle) / 360;
float rightSpeed = (rightDistance / time) / maxSpeed * speed;
*/

void MovementTwoMotors::_calculateSpeedDistance(float speed, bool innerWheel, int radius, int angle, float *finalSpeed, float *finalDistance)
{
}
