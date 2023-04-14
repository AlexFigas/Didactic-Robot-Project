#ifndef MOVEMENTTWOMOTORS_H
#define MOVEMENTTWOMOTORS_H

#include "Movement.h"

class MovementTwoMotors : public Movement
{
public:
    MovementTwoMotors(Motor *motors, float wheelbase, float wheelRadius);

    void left(int radius, int angle, int speed) override;
    void right(int radius, int angle, int speed) override;

private:

    void _calculateSpeedDistance(bool leftMotor, int radius, int angle, int speed, float* finalSpeed, float* finalDistance);
};

#endif
