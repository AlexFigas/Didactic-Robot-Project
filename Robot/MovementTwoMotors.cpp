#include "MovementTwoMotors.h"

MovementTwoMotors::MovementTwoMotors(Motor *motors, float track, float wheelRadius) : Movement(motors, track, wheelRadius)
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

void MovementTwoMotors::_calculateSpeedDistance(bool innerWheel, int radius, int angle, int speed, float* finalSpeed, float* finalDistance)
{
    // RobotRadius (Track / 2)
    float robotRadius = getTrack() / 2;
    robotRadius = (innerWheel) ? -robotRadius : robotRadius;

    // Wheel perimeter (Distance in cm in one turn of the wheel)
    float wheelPerimeter = getWheelRadius() * 2.0 * PI;

    // Speed in cm/s of the robot wheel in one revolution per minute (RPM). This calculation
    // is necessary because the speed scale passed as a parameter (speed) is a fraction of the
    // maximum allowed speed and is not directly related to the actual speed of the robot wheel.
    float velocity = speed * _MAX_SPEED;
    velocity = velocity * wheelPerimeter / 60.0;

    // Convert the speed scale from 0 to 100 to a decimal fraction between 0 and 1,
    // which is multiplied by the robot's maximum speed to get the actual speed in cm/s
    velocity = velocity / _MAX_SPEED;

    // Average linear speed of the wheels
    // (The velocity of the outer wheel is equal to velocity variable value)
    float velocityWheel = velocity * (2.0 + robotRadius / radius) / 2;
    float time = angle * PI / 180.0 / velocity;

    *finalSpeed = velocityWheel / _MAX_SPEED * 100.0;
    *finalDistance = velocityWheel * time;
}

