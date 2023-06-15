#ifndef MOVEMENTTWOMOTORS_H
#define MOVEMENTTWOMOTORS_H

#include "Movement.h"
#include <iostream>
#include <cmath>

class MovementTwoMotors : public Movement
{
public:
    MovementTwoMotors(Motor *motors, float track, float wheelRadius);

    void curve(float speed, int radius, int angle, bool isLeft = true) override;
    void left(float speed, int radius, int angle) override;
    void right(float speed, int radius, int angle) override;

private:
    void _calculateSpeedDistance(float speed, bool leftMotor, int radius, int angle, float *finalSpeed, float *finalDistance);
    void _waitForTarget();
};

#endif
