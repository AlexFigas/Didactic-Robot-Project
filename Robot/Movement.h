#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motor.h"
#include <thread>
#include <atomic>

class Movement
{
public:
    Movement(Motor *motors, float track, float wheelRadius);

    void begin();

    void front(int speed, float length);
    void back(int speed, float length);
    void stop(bool now);
    void slow();
    void block();
    void reset();

    void line(int speed, float length, bool isFront = true);
    virtual void left(int radius, int angle, int speed) = 0;
    virtual void right(int radius, int angle, int speed) = 0;

    float getTrack();
    float getWheelRadius();
    Motor *getMotors();

protected:
    int _numMotors;
    int _MAX_SPEED = 100;   // Max speed (0% - 100%)
    int _DELAY_MOTORS = 50; // Delay motors start up
    int _PERIOD = 100;

private:
    void _waitForTargetInterrupt(int speed);

    float _track;       // Distance between wheels (cm)
    float _wheelRadius; // Wheel radius (cm)
    Motor *_motors;
};
#endif
