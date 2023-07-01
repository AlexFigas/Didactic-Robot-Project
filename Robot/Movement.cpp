#include "Movement.h"

extern BluetoothSerial _serialBT;

int indexDataLine;
Data dataLine[length];
int indexDataCurve;
Data dataCurve[length];

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

    indexDataLine = 0;
    dataLine[indexDataLine].pwmLeft = _motors[MOTOR_LEFT].getPWM();
    dataLine[indexDataLine].pwmRight = _motors[MOTOR_RIGHT].getPWM();
    dataLine[indexDataLine].ticksLeft = _motors[MOTOR_LEFT].getCounter();
    dataLine[indexDataLine].ticksRight = _motors[MOTOR_RIGHT].getCounter();
    dataLine[indexDataLine].ratio = 0.0f;

    directionLineCalibration();

    // Stops and resets the counters
    slow();
    block();
    reset();

    //char auxBuffer[80];
    // sprintf(auxBuffer, "index;pwmLeft;pwmRight;ticksLeft;ticksRight;ratio");
    // SerialBT.println(auxBuffer);

    //for (int i = 0; i < length; i++)
    //{
    //    sprintf(auxBuffer, "%d;%d;%d;%d;%f", dataLine[i].pwmLeft, dataLine[i].pwmRight, dataLine[i].ticksLeft, dataLine[i].ticksRight, dataLine[i].ratio);
    //    SerialBT.println(auxBuffer);
    //}
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
