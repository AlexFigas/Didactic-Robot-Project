#include "MovementTwoMotors.h"

MovementTwoMotors::MovementTwoMotors(Motor *motors, int wheelbase) : Movement(motors, wheelbase)
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

            // Distance and time it takes the center of the robot to reach
            float distance = (2 * PI * radius * angle) / 360;
            float time = distance / speed;

            // Speed ​​calculation for the left motor
            float leftDistance = (2 * PI * (radius - (getWheelbase() / 2)) * angle) / 360;
            float leftSpeed = leftDistance / time;

            // Speed ​​calculation for the right motor
            float rightDistance = (2 * PI * (radius + (getWheelbase() / 2)) * angle) / 360;
            float rightSpeed = rightDistance / time;

            // In case the speed exceeds the scale values [0 - 100]
            float delta = rightSpeed - 100;

            if (delta > 0)
            {
                leftSpeed -= delta;
                rightSpeed -= delta;
            }

            // Set the direction and speed of each motor to turn in the appropriate direction to make the robot move in a leftward curve. This can be done by using the setDirection() method of the Motor class and passing in the appropriate direction (e.g., forward for the left motors and backward for the right motors).
            getMotors()[0].front(leftSpeed, leftDistance);
            delay(50);
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

            // Distance and time it takes the center of the robot to reach
            float distance = (2 * PI * radius * angle) / 360;
            float time = distance / speed;

            // Speed ​​calculation for the left motor
            float leftDistance = (2 * PI * (radius + (getWheelbase() / 2)) * angle) / 360;
            float leftSpeed = leftDistance / time;

            // Speed ​​calculation for the right motor
            float rightDistance = (2 * PI * (radius - (getWheelbase() / 2)) * angle) / 360;
            float rightSpeed = rightDistance / time;

            // In case the speed exceeds the scale values [0 - 100]
            float delta = leftSpeed - 100;

            if (delta > 0)
            {
                leftSpeed -= delta;
                rightSpeed -= delta;
            }

            // Set the direction and speed of each motor to turn in the appropriate direction to make the robot move in a rightward curve. This can be done by using the setDirection() method of the Motor class and passing in the appropriate direction (e.g., forward for the right motors and backward for the left motors).
            getMotors()[0].front(rightSpeed, rightDistance);
            delay(50);
            getMotors()[1].front(leftSpeed, leftDistance);
        }
        else
        {
            // TODO
        }
    }
}
