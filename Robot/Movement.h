#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motor.h"

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
// TODO
#define _PERIOD 50
#define _EXEC_TIME 6000

class Movement
{
public:
    Movement(Motor *motors, float track, float wheelRadius);

    void begin();

    void line(float speed, float length, bool isFront = true);
    void front(float speed, float length);
    void back(float speed, float length);

    virtual void curve(float speed, int radius, int angle, bool isLeft = true) = 0;
    virtual void left(float speed, int radius, int angle) = 0;
    virtual void right(float speed, int radius, int angle) = 0;

    void stop(bool now);
    void slow();
    void block();

    void reset();

    float getTrack();
    float getWheelRadius();
    Motor *getMotors();

    String result;

protected:
    int _numMotors;
    float _MAX_SPEED = 100.0; // Max speed (0% - 100%)
    int _DELAY_MOTORS = 50;   // Delay motors start up
    

private:
    void _waitForTargetInterrupt();

    float _track;       // Distance between wheels (cm)
    float _wheelRadius; // Wheel radius (cm)
    Motor *_motors;
};
#endif
