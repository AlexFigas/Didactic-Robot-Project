#include "Movement.h"

extern BluetoothSerial _serialBT;

int indexDataLine;
Data dataLine[length];
int indexDataCurve;
Data dataCurve[length];

Movement::Movement(Motor** motors, int numMotors, float track) : motors(motors), _numMotors(numMotors), _track(track) {}

float Movement::getTrack()
{
    return _track;
}
Motor** Movement::getMotors()
{
    return motors;
}

void Movement::begin()
{
    for (int i = 0; i < _numMotors; ++i)
        motors[i]->begin();
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
    dataLine[indexDataLine].pwmLeft = motors[MOTOR_LEFT]->getPWM();
    dataLine[indexDataLine].pwmRight = motors[MOTOR_RIGHT]->getPWM();
    dataLine[indexDataLine].ticksLeft = motors[MOTOR_LEFT]->getCounter();
    dataLine[indexDataLine].ticksRight = motors[MOTOR_RIGHT]->getCounter();
    dataLine[indexDataLine].ratio = 0.0f;

    directionLineCalibration();

    // Stops and resets the counters
    slow();
    block();
    reset();
}

void Movement::front(float speed, float length)
{
    for (int i = 0; i < _numMotors; ++i)
        motors[i]->front(speed, length);
}

void Movement::back(float speed, float length)
{
    for (int i = 0; i < _numMotors; ++i)
        motors[i]->back(speed, length);
}

void Movement::slow()
{
    for (int i = 0; i < _numMotors; ++i)
        motors[i]->slow();
}

void Movement::block()
{
    for (int i = 0; i < _numMotors; ++i)
        motors[i]->block();
}

void Movement::stop()
{
    for (int i = 0; i < _numMotors; ++i)
        motors[i]->stop();
}

void Movement::reset()
{
    for (int i = 0; i < _numMotors; ++i)
        motors[i]->resetCounter();
}