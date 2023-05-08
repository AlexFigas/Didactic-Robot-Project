#ifndef MOVEMENTTWOMOTORS_H
#define MOVEMENTTWOMOTORS_H

#include "Movement.h"
#include <iostream>
#include <cmath>

class MovementTwoMotors : public Movement
{
public:
    MovementTwoMotors(Motor *motors, float track, float wheelRadius);

    void left(int radius, int angle, int speed) override;
    void right(int radius, int angle, int speed) override;

private:

    void _calculateSpeedDistance(bool leftMotor, int radius, int angle, int speed, float* finalSpeed, float* finalDistance);
};

#endif
