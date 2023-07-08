#include "MovementTwoMotors.h"

//extern BluetoothSerial SerialBT;

MovementTwoMotors::MovementTwoMotors(Motor *motors, float track) : Movement(motors, track)
{
    _numMotors = 2;
}

void MovementTwoMotors::curve(float speed, float radius, float angle, bool isLeft)
{
    float targetSpeed = speed < _MIN_SPEED ? _MIN_SPEED : (speed > _MAX_SPEED ? _MAX_SPEED : speed);

    reset();

    if (isLeft == true)
    {
        left(targetSpeed, radius, angle);
    }
    else
    {
        right(targetSpeed, radius, angle);
    }

    indexDataCurve = 0;
    dataCurve[indexDataCurve].pwmLeft = _motors[MOTOR_LEFT].getPWM();
    dataCurve[indexDataCurve].pwmRight = _motors[MOTOR_RIGHT].getPWM();
    dataCurve[indexDataCurve].ticksLeft = _motors[MOTOR_LEFT].getCounter();
    dataCurve[indexDataCurve].ticksRight = _motors[MOTOR_RIGHT].getCounter();
    dataCurve[indexDataCurve].ratio = 0.0f;

    directionCurveCalibration();

    // Stops and resets the counters
    slow();
    block();
    reset();

    /*char auxBuffer[80];
    sprintf(auxBuffer, "index;pwmLeft;pwmRight;ticksLeft;ticksRight;ratio");
    SerialBT.print(auxBuffer);

    // Serial.println(auxBuffer);
    for (int i = 0; i < length; i++)
    {
        sprintf(auxBuffer, "%d;%d;%d;%d;%d;%f", i, dataCurve[i].pwmLeft, dataCurve[i].pwmRight, dataCurve[i].ticksLeft, dataCurve[i].ticksRight, dataCurve[i].ratio);
        SerialBT.print(auxBuffer);
    }*/
}

void MovementTwoMotors::left(float speed, float radius, float angle)
{
    if (radius == 0)
    {
        // TODO
    }
    else
    {
        // Desired speed for each motor
        float track2 = getTrack() / 2.0;
        float leftSpeed = ((radius - track2) / radius) * speed;
        float rightSpeed = ((radius + track2) / radius) * speed;

        // Adjust values ​​to within limits
        float leftDiff = leftSpeed < _MIN_SPEED ? _MIN_SPEED - leftSpeed : (leftSpeed > _MAX_SPEED ? _MAX_SPEED - leftSpeed : 0);
        float rightDiff = rightSpeed < _MIN_SPEED ? _MIN_SPEED - rightSpeed : (rightSpeed > _MAX_SPEED ? _MAX_SPEED - rightSpeed : 0);
        leftSpeed = leftSpeed + rightDiff + leftDiff < _MIN_SPEED ? _MIN_SPEED : (leftSpeed + rightDiff + leftDiff > _MAX_SPEED ? _MAX_SPEED : leftSpeed + leftDiff + rightDiff);
        rightSpeed = rightSpeed + rightDiff + leftDiff < _MIN_SPEED ? _MIN_SPEED : (rightSpeed + rightDiff + leftDiff > _MAX_SPEED ? _MAX_SPEED : rightSpeed + rightDiff + leftDiff);

        // Distance to travel for each wheel
        float leftDistance = (2.0 * PI * (radius - track2) * angle) / 360.0;
        float rightDistance = (2.0 * PI * (radius + track2) * angle) / 360.0;

        getMotors()[MOTOR_LEFT].front(leftSpeed, leftDistance);
        getMotors()[MOTOR_RIGHT].front(rightSpeed, rightDistance);
    }
}

void MovementTwoMotors::right(float speed, float radius, float angle)
{
    if (radius == 0)
    {
        // TODO
    }
    else
    {
        // Desired speed for each motor
        float track2 = getTrack() / 2.0;
        float leftSpeed = ((radius + track2) / radius) * speed;
        float rightSpeed = ((radius - track2) / radius) * speed;

        // Adjust values ​​to within limits
        float leftDiff = leftSpeed < _MIN_SPEED ? _MIN_SPEED - leftSpeed : (leftSpeed > _MAX_SPEED ? _MAX_SPEED - leftSpeed : 0);
        float rightDiff = rightSpeed < _MIN_SPEED ? _MIN_SPEED - rightSpeed : (rightSpeed > _MAX_SPEED ? _MAX_SPEED - rightSpeed : 0);
        leftSpeed = leftSpeed + rightDiff + leftDiff < _MIN_SPEED ? _MIN_SPEED : (leftSpeed + rightDiff + leftDiff > _MAX_SPEED ? _MAX_SPEED : leftSpeed + leftDiff + rightDiff);
        rightSpeed = rightSpeed + rightDiff + leftDiff < _MIN_SPEED ? _MIN_SPEED : (rightSpeed + rightDiff + leftDiff > _MAX_SPEED ? _MAX_SPEED : rightSpeed + rightDiff + leftDiff);

        // Distance to travel for each wheel
        float leftDistance = (2.0 * PI * (radius - track2) * angle) / 360.0;
        float rightDistance = (2.0 * PI * (radius + track2) * angle) / 360.0;

        getMotors()[MOTOR_LEFT].front(leftSpeed, leftDistance);
        getMotors()[MOTOR_RIGHT].front(rightSpeed, rightDistance);
    }
}

void MovementTwoMotors::directionCurveCalibration()
{
    unsigned long timeout = millis() + _PERIOD * _SAMPLES_TO_SKIP;
    unsigned long finalTime = millis() + _EXEC_TIME;

    int currentLeftCounter = _motors[MOTOR_LEFT].getCounter();
    int currentRightCounter = _motors[MOTOR_RIGHT].getCounter();

    int leftTarget = _motors[MOTOR_LEFT].getTargetInterrupt();
    int rightTarget = _motors[MOTOR_RIGHT].getTargetInterrupt();

    float k = (float)(leftTarget) / (float)(rightTarget);

    //char auxBuffer[80];
    //sprintf(auxBuffer, "leftTarget: %d ; rightTarget: %d ; flag: %d", leftTarget, rightTarget, (int)(currentLeftCounter < leftTarget || currentRightCounter < rightTarget));
    //SerialBT.println(auxBuffer);

    while ((currentLeftCounter < leftTarget || currentRightCounter < rightTarget))
    {
        // Passado PERIOD entra
        unsigned long currentTime = millis();
        if (currentTime >= timeout)
        {
            // Obtem o numero de interrupts atual de cada roda
            currentLeftCounter = _motors[MOTOR_LEFT].getCounter();
            currentRightCounter = _motors[MOTOR_RIGHT].getCounter();

            int diffLeft = currentLeftCounter - dataCurve[indexDataCurve].ticksLeft;
            int diffRight = currentRightCounter - dataCurve[indexDataCurve].ticksRight;

            timeout = currentTime + _PERIOD;

            int maxDiff = max(diffLeft, diffRight);
            int minDiff = min(diffLeft, diffRight);
            float ratio = 0.0f;

            float motorDif;
            float rightSpeed, leftSpeed;

            /*if (minDiff > 0)
            {
                ratio = (float)(maxDiff) / (float)(minDiff);
                float ratioAux = (ratio - k) / 2.0;
                float ratioAdd = k + ratioAux;
                float ratioSub = k - ratioAux;

                if (diffLeft > diffRight)
                {
                    rightSpeed = _motors[MOTOR_RIGHT].getPWM() * ratioAdd;
                    leftSpeed = _motors[MOTOR_LEFT].getPWM() * ratioSub;
                }
                else
                {
                    rightSpeed = _motors[MOTOR_RIGHT].getPWM() * ratioSub;
                    leftSpeed = _motors[MOTOR_LEFT].getPWM() * ratioAdd;
                }

                float motorDif_right = rightSpeed < _MIN_PWM ? _MIN_PWM - rightSpeed : (rightSpeed > _MAX_PWM ? _MAX_PWM-rightSpeed : 0);
                float motorDif_left = leftSpeed < _MIN_PWM ? _MIN_PWM - leftSpeed : (leftSpeed > _MAX_PWM ? _MAX_PWM-leftSpeed : 0);

                rightSpeed = rightSpeed+motorDif_left < _MIN_PWM ? _MIN_PWM : (rightSpeed+motorDif_left > _MAX_PWM ? _MAX_PWM : rightSpeed+motorDif_left);
                leftSpeed = leftSpeed+motorDif_right < _MIN_PWM ? _MIN_PWM : (leftSpeed+motorDif_right > _MAX_PWM ? _MAX_PWM : leftSpeed+motorDif_right);

                _motors[MOTOR_RIGHT].setPWM(rightSpeed);
                _motors[MOTOR_LEFT].setPWM(leftSpeed);

                ++indexDataCurve;
                dataCurve[indexDataCurve].pwmLeft = _motors[MOTOR_LEFT].getPWM();
                dataCurve[indexDataCurve].pwmRight = _motors[MOTOR_RIGHT].getPWM();
                dataCurve[indexDataCurve].ticksLeft = currentLeftCounter;
                dataCurve[indexDataCurve].ticksRight = currentRightCounter;
                dataCurve[indexDataCurve].ratio = ratio;
            }*/
        }
    }
}

void MovementTwoMotors::directionLineCalibration()
{
    unsigned long timeout = millis() + _PERIOD * _SAMPLES_TO_SKIP;
    unsigned long finalTime = millis() + _EXEC_TIME;

    int currentLeftCounter = _motors[MOTOR_LEFT].getCounter();
    int currentRightCounter = _motors[MOTOR_RIGHT].getCounter();

    int leftTarget = _motors[MOTOR_LEFT].getTargetInterrupt();
    int rightTarget = _motors[MOTOR_RIGHT].getTargetInterrupt();

    while ((currentLeftCounter < leftTarget || currentRightCounter < rightTarget))
    {
        // Passado PERIOD entra
        unsigned long currentTime = millis();
        if (currentTime >= timeout)
        {
            // Obtem o numero de interrupts atual de cada roda
            currentLeftCounter = _motors[MOTOR_LEFT].getCounter();
            currentRightCounter = _motors[MOTOR_RIGHT].getCounter();

            int diffLeft = currentLeftCounter - dataLine[indexDataLine].ticksLeft;
            int diffRight = currentRightCounter - dataLine[indexDataLine].ticksRight;

            timeout = currentTime + _PERIOD;

            int maxDiff = max(diffLeft, diffRight);
            int minDiff = min(diffLeft, diffRight);
            float ratio = 0.0f;

            float motorDif;
            float rightSpeed, leftSpeed;

            if (minDiff > 0)
            {
                ratio = (float)(maxDiff) / (float)(minDiff);
                float ratioAux = (ratio - 1.0) / 2.0;
                float ratioAdd = 1.0 + ratioAux;
                float ratioSub = 1.0 - ratioAux;

                if (diffLeft > diffRight)
                {
                    rightSpeed = _motors[MOTOR_RIGHT].getPWM() * ratioAdd;
                    leftSpeed = _motors[MOTOR_LEFT].getPWM() * ratioSub;
                }
                else
                {
                    rightSpeed = _motors[MOTOR_RIGHT].getPWM() * ratioSub;
                    leftSpeed = _motors[MOTOR_LEFT].getPWM() * ratioAdd;
                }

                float motorDif_right = rightSpeed < _MIN_PWM ? _MIN_PWM - rightSpeed : (rightSpeed > _MAX_PWM ? _MAX_PWM - rightSpeed : 0);
                float motorDif_left = leftSpeed < _MIN_PWM ? _MIN_PWM - leftSpeed : (leftSpeed > _MAX_PWM ? _MAX_PWM - leftSpeed : 0);

                rightSpeed = rightSpeed + motorDif_left < _MIN_PWM ? _MIN_PWM : (rightSpeed + motorDif_left > _MAX_PWM ? _MAX_PWM : rightSpeed + motorDif_left);
                leftSpeed = leftSpeed + motorDif_right < _MIN_PWM ? _MIN_PWM : (leftSpeed + motorDif_right > _MAX_PWM ? _MAX_PWM : leftSpeed + motorDif_right);

                _motors[MOTOR_RIGHT].setPWM(rightSpeed);
                _motors[MOTOR_LEFT].setPWM(leftSpeed);

                ++indexDataLine;
                dataLine[indexDataLine].pwmLeft = _motors[MOTOR_LEFT].getPWM();
                dataLine[indexDataLine].pwmRight = _motors[MOTOR_RIGHT].getPWM();
                dataLine[indexDataLine].ticksLeft = currentLeftCounter;
                dataLine[indexDataLine].ticksRight = currentRightCounter;
                dataLine[indexDataLine].ratio = ratio;
            }
        }
    }
}
