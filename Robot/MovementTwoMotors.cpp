#include "MovementTwoMotors.h"

MovementTwoMotors::MovementTwoMotors(Motor *motors, float track, float wheelRadius) : Movement(motors, track, wheelRadius)
{
    _numMotors = 2;
}

void MovementTwoMotors::curve(int speed, int radius, int angle, bool isLeft)
{
    if (isLeft == true)
    {
        left(radius, angle, speed);
    }
    else 
    {
        right(radius, angle, speed);
    }
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
            // Distance and time it takes the center of the robot to reach
            float distance = (2 * PI * radius * angle) / 360;
            float time = distance / speed;

            // Speed ​​calculation for the inner motor
            float leftDistance = (2 * PI * (radius - (getTrack() / 2)) * angle) / 360;
            float leftSpeed = leftDistance / time;

            float rightDistance = (2 * PI * (radius + (getTrack() / 2)) * angle) / 360;
            float rightSpeed = rightDistance / time;

            // Force the minimum speed to be equal to _MAX_SPEED / 2
            float offset = 0;
            if (leftSpeed < (_MAX_SPEED / 2))
            {
                offset = (_MAX_SPEED / 2) - leftSpeed;
            }
            else if (rightSpeed < (_MAX_SPEED / 2))
            {
                offset = (_MAX_SPEED / 2) - rightSpeed;
            }

            // Activate motors
            getMotors()[0].front(leftSpeed + offset, leftDistance);
            delay(_DELAY_MOTORS);
            getMotors()[1].front(rightSpeed + offset, rightDistance);
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
            // Distance and time it takes the center of the robot to reach
            float distance = (2 * PI * radius * angle) / 360;
            float time = distance / speed;

            // Speed ​​calculation for the inner motor
            float leftDistance = (2 * PI * (radius + (getTrack() / 2)) * angle) / 360;
            float leftSpeed = leftDistance / time;

            float rightDistance = (2 * PI * (radius - (getTrack() / 2)) * angle) / 360;
            float rightSpeed = rightDistance / time;

            float offset = 0;
            if (leftSpeed < (_MAX_SPEED / 2))
            {
                offset = (_MAX_SPEED / 2) - leftSpeed;
            }
            else if (rightSpeed < (_MAX_SPEED / 2))
            {
                offset = (_MAX_SPEED / 2) - rightSpeed;
            }

            // Activate motors
            getMotors()[0].front(leftSpeed + offset, leftDistance);
            delay(_DELAY_MOTORS);
            getMotors()[1].front(rightSpeed + offset, rightDistance);
        }
        else
        {
            // TODO
        }
    }
}

/*
// Distance and time it takes the center of the robot to reach
float distance = (2 * M_PI * radius * angle) / 360;
float time = distance / speed;

// Maximum speed for each motor
float maxSpeed = 100; // adjust as needed

// Speed ​​calculation for the left motor
float leftDistance = (2 * M_PI * (radius - (_wheelbase / 2)) * angle) / 360;
float leftSpeed = (leftDistance / time) / maxSpeed * speed;

// Speed ​​calculation for the right motor
float rightDistance = (2 * M_PI * (radius + (_wheelbase / 2)) * angle) / 360;
float rightSpeed = (rightDistance / time) / maxSpeed * speed;
*/

void MovementTwoMotors::_calculateSpeedDistance(bool innerWheel, int radius, int angle, int speed, float* finalSpeed, float* finalDistance)
{



}

