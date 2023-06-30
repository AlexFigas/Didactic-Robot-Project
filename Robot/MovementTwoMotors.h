#ifndef MOVEMENTTWOMOTORS_H
#define MOVEMENTTWOMOTORS_H

#include "Movement.h"
#include <iostream>
#include <cmath>

class MovementTwoMotors : public Movement
{
public:
    MovementTwoMotors(Motor *motors, float track);

    void curve(float speed, float radius, float angle, bool isLeft = true) override;
    void left(float speed, float radius, float angle) override;
    void right(float speed, float radius, float angle) override;

private:
    void _directionCurveCalibration();
};

#endif
