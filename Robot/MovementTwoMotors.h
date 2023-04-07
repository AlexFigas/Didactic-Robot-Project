#ifndef MOVEMENTTWOMOTORS_H
#define MOVEMENTTWOMOTORS_H

#include "Movement.h"

class MovementTwoMotors : public Movement
{
public:
    MovementTwoMotors(Motor *motors, int wheelbase);

    void left(int radius, int angle, int speed) override;
    void right(int radius, int angle, int speed) override;
};

#endif
