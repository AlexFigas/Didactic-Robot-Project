#include "MovementTwoMotors.h"

MovementTwoMotors::MovementTwoMotors(Motor *motors, float wheelbase, float wheelRadius) : Movement(motors, wheelbase, wheelRadius)
{
    _numMotors = 2;
}

void MovementTwoMotors::left(int radius, int angle, int speed)
{
    if (radius == 0)
    {
        // TODO
    }            
    else
    {
        if (angle > 0)
        {
            // Variables
            float leftSpeed, rightSpeed;
            float leftDistance, rightDistance;

            // Calculation ​
            _calculateSpeedDistance(true, radius, angle, speed, &leftSpeed, &leftDistance);
            _calculateSpeedDistance(false, radius, angle, speed, &rightSpeed, &rightDistance); 

            // Activate motors
            getMotors()[0].front(leftSpeed, leftDistance);
            delay(_DELAY_MOTORS);
            getMotors()[1].front(rightSpeed, rightDistance);
        }
        else
        {
            // TODO
        }
    }
}

void MovementTwoMotors::right(int radius, int angle, int speed)
{
    if (radius == 0)
    {
        // TODO
    }
    else
    {
        if (angle > 0)
        {
            // Variables
            float leftSpeed, rightSpeed;
            float leftDistance, rightDistance;

            // Calculation ​
            _calculateSpeedDistance(false, radius, angle, speed, &leftSpeed, &leftDistance);
            _calculateSpeedDistance(true, radius, angle, speed, &rightSpeed, &rightDistance); 

            // Activate motors
            getMotors()[0].front(leftSpeed, leftDistance);
            delay(_DELAY_MOTORS);
            getMotors()[1].front(rightSpeed, rightDistance);
        }
        else
        {
            // TODO
        }
    }
}

void MovementTwoMotors::_calculateSpeedDistance(bool leftMotor, int radius, int angle, int speed, float* finalSpeed, float* finalDistance)
{
    // RobotRadius
    float robotRadius = getWheelbase() / 2;
    robotRadius = (leftMotor) ? -robotRadius : robotRadius;

    // Wheel perimeter
    float wheelPerimeter = getWheelRadius() * 2.0 * PI;

    // Multiply the input speed by the maximum speed value
    float inputVelocity = speed * _MAX_SPEED;

    // RPM to RPS conversion
    float velocityRPS = inputVelocity * wheelPerimeter / 60.0;

    // RPS to cm/s conversion
    float velocitycms = velocityRPS / 100.0;

    // Velocity
    float velocityWheel = velocitycms * (2.0 + robotRadius / radius) / 2.0;

    // Time to do the required angle
    float time = angle * PI / 180.0 / velocitycms;

    // Final speed and distance
    *finalSpeed = velocityWheel / _MAX_SPEED * 100.0;
    *finalDistance = velocityWheel * time;
}
