#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motor.h"

class Movement
{
public:
    Movement(Motor *motors, int wheelbase);

    void begin();

    void front(int speed);
    void back(int speed);
    void stop(bool now);

    virtual void left(int radius, int angle, int speed) = 0;
    virtual void right(int radius, int angle, int speed)= 0;

    int getWheelbase();
    Motor *getMotors();

protected:
    int _numMotors;

private:
    int _wheelbase; // cm (distance between wheels)
    Motor *_motors;
};
#endif
