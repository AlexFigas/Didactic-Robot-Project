#include "Movement.h"

Movement::Movement(TwoMotors motors, int wheelbase)
{
    _motors = new Motor[2]{motors.left, motors.right};
    _motors[0] = motors.left;
    _motors[1] = motors.right;

    _wheelbase = wheelbase;
}

Movement::Movement(FourMotors motors, int wheelbase)
{
    /*_motors = new Motor[4];
    _motors[0] = motors.frontLeft;
    _motors[1] = motors.frontRight;
    _motors[2] = motors.backLeft;
    _motors[3] = motors.backRight;
*/
    _wheelbase = wheelbase;
}

void Movement::begin()
{
    for (int i = 0; i < sizeof(_motors); i++)
    {
        _motors[i].begin();
    }
}

void Movement::front(int speed)
{
    for (int i = 0; i < sizeof(_motors); i++)
    {
        _motors[i].front(speed);
    }
}

void Movement::back(int speed)
{
    for (int i = 0; i < sizeof(_motors); i++)
    {
        _motors[i].setSpeed(speed);
        _motors[i].back(speed);
    }
}

void Movement::left(int radius, int angle, int speed)
{
    if (radius == 0)
    {
        // TODO
    }
    else
    {
        if (angle > 0)
        {
            /*
                Robot wheels are arranged like this:

                0 1
                2 3
            */

            // Calculate the speed of the inner and outer wheels
            //float innerSpeed = (2 * PI * (radius - (_wheelbase / 2.0)) * (angle / 360.0)) / (2 * PI * radius * (angle / 360.0)) * speed;
            //float outerSpeed = speed;

            // Distance and time it takes the center of the robot to reach
            float distance = (2 * PI * radius * angle) / 360;
            float time = distance / speed;

            // Speed ​​calculation for the left motor
            float leftDistance = (2 * PI * (radius - (_wheelbase / 2)) * angle) / 360;
            float leftSpeed = leftDistance / time;

            // Speed ​​calculation for the right motor
            float rightDistance = (2 * PI * (radius + (_wheelbase / 2)) * angle) / 360;
            float rightSpeed = rightDistance / time;

            // In case the speed exceeds the scale values [0 - 100]
            float delta = max(leftSpeed, rightSpeed) - 100;

            if (delta > 0)
            {
                leftSpeed -= delta;
                rightSpeed -= delta;
            }

            Serial.print("Left: ");
            Serial.println(leftSpeed);
            Serial.print("Right: ");
            Serial.println(rightSpeed);

            // Set the direction and speed of each motor to turn in the appropriate direction to make the robot move in a leftward curve. This can be done by using the setDirection() method of the Motor class and passing in the appropriate direction (e.g., forward for the left motors and backward for the right motors).
            _motors[0].front(leftSpeed, leftDistance);
            _motors[1].front(rightSpeed, rightDistance);
            //_motors[2].front(leftSpeed);
            //_motors[3].front(rightSpeed);
        }
        else
        {
            // TODO
        }
    }
}

void Movement::right(int radius, int angle, int speed)
{
    // TODO
}

void Movement::stop(bool now)
{
    for (int i = 0; i < sizeof(_motors); i++)
    {
        _motors[i].stop(now);
    }
}
