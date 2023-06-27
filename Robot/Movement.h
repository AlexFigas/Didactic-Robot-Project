#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motor.h"

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
// TODO
#define _PERIOD 50
#define _EXEC_TIME 3000
#define _SAMPLES_TO_SKIP 4

int const length = (_EXEC_TIME / _PERIOD) - (_SAMPLES_TO_SKIP - 1); // Comprimento do array (20)

struct Data
{
    int pwmLeft;
    int ticksLeft;
    int pwmRight;
    int ticksRight;
    float ratio;
};



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

    void stop();
    void slow();
    void block();

    void reset();

    float getTrack();
    float getWheelRadius();
    Motor *getMotors();

protected:
    int _numMotors;
    int _MAX_SPEED = 4095; // Max motor speed (50% - 100%)
    int _MIN_SPEED = 2048;  // Min motor speed (50% - 100%)
    int _DELAY_MOTORS = 50;  // Delay motors start up
    Motor *_motors;

private:
    void _waitForTargetInterrupt();

    float _initial_speed;
    float _track;       // Distance between wheels (cm)
    float _wheelRadius; // Wheel radius (cm)
};
#endif
