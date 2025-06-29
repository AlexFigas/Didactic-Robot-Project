#include "Movement.h"

extern BluetoothSerial _serialBT;

int indexDataLine;
Data dataLine[length];
int indexDataCurve;
Data dataCurve[length];

Movement::Movement(Motor* left, Motor* right, float track) : leftMotor(left), rightMotor(right), _track(track) {}

float Movement::getTrack()
{
    return _track;
}

void Movement::begin()
{
    leftMotor->begin();
    rightMotor->begin();
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
    dataLine[indexDataLine].pwmLeft = leftMotor->getPWM();
    dataLine[indexDataLine].pwmRight = rightMotor->getPWM();
    dataLine[indexDataLine].ticksLeft = leftMotor->getCounter();
    dataLine[indexDataLine].ticksRight = rightMotor->getCounter();
    dataLine[indexDataLine].ratio = 0.0f;

    directionLineCalibration();

    // Stops and resets the counters
    slow();
    block();
    reset();
}

void Movement::front(float speed, float length)
{
    leftMotor->front(speed, length);
    rightMotor->front(speed, length);
}

void Movement::back(float speed, float length)
{
    leftMotor->back(speed, length);
    rightMotor->back(speed, length);
}

void Movement::slow()
{
    leftMotor->slow();
    rightMotor->slow();
}

void Movement::block()
{
    leftMotor->block();
    rightMotor->block();
}

void Movement::stop()
{
    leftMotor->stop();
    rightMotor->stop();
}

void Movement::reset()
{
    leftMotor->resetCounter();
    rightMotor->resetCounter();
}