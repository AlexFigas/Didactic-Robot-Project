#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motor.h"

class Movement
{
public:
    struct TwoMotors
    {
        Motor left;
        Motor right;
    };

    struct FourMotors
    {
        Motor frontLeft;
        Motor frontRight;
        Motor backLeft;
        Motor backRight;
    };

    Movement(TwoMotors motors, int wheelbase);
    Movement(FourMotors motors, int wheelbase);

    void begin();

    void front(int speed);
    void back(int speed);
    void left(int radius, int angle, int speed);
    void right(int radius, int angle, int speed);
    void stop(bool now);

private:
    Motor *_motors;
    int _wheelbase; // cm (distance between wheels)
};
#endif
