/**
 * @file Movement.h - Library for controlling the movement of a robot.
 *
 * @author Alexandre Figueiredo and Daniela Gonçalves
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Motor.h"
#include <BluetoothSerial.h>

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
#define _PERIOD 50
#define _EXEC_TIME 3000
#define _SAMPLES_TO_SKIP 4

int const length = (_EXEC_TIME / _PERIOD) - (_SAMPLES_TO_SKIP - 1); // Size of the array

/**
 * @brief Struct representing a data sample.
 */
struct Data
{
    int pwmLeft;
    int pwmRight;
    int ticksLeft;
    int ticksRight;
    float ratio;
};

extern int indexDataLine;      // Debug index data
extern Data dataLine[length];  // Debug data
extern int indexDataCurve;     // Debug index data curve
extern Data dataCurve[length]; // Debug data curve

/**
 * @brief Class representing the movement of a robot.
 *
 * This class is responsible for controlling the movement of a robot.
 * It uses the Motor class to control the motors.
 */
class Movement
{
public:
    /**
     * @brief Construct a new Movement object
     *
     * @param motors - An array of Motor objects.
     * @param track - The track of the robot in centimeters.
     */
    Movement(Motor *motors, float track);

    /**
     * @brief Initializes the motors.
     * This method should be called once at the beginning of the program.
     */
    void begin();

    /**
     * @brief Moves the robot in a straight line.
     *
     * @param speed - The speed of the robot in percentage.
     * @param length - The length of the line in centimeters.
     * @param isFront - The direction of the movement. True for forward, false for backward.
     */
    void line(float speed, float length, bool isFront = true);

    /**
     * @brief Moves the robot forward.
     *
     * @param speed - The speed of the robot in percentage.
     * @param length - The length of the line in centimeters.
     */
    void front(float speed, float length);

    /**
     * @brief Moves the robot backward.
     *
     * @param speed - The speed of the robot in percentage.
     * @param length - The length of the line in centimeters.
     */
    void back(float speed, float length);

    /**
     * @brief Moves the robot in a curve.
     *
     * @param speed - The speed of the robot in percentage.
     * @param radius - The radius of the curve in centimeters.
     * @param angle - The angle of the curve in degrees.
     * @param isLeft - The direction of the curve. True for left, false for right.
     */
    virtual void curve(float speed, float radius, float angle, bool isLeft = true) = 0;

    /**
     * @brief Moves the robot in a curve to the left.
     *
     * @param speed - The speed of the robot in percentage.
     * @param radius - The radius of the curve in centimeters.
     * @param angle - The angle of the curve in degrees.
     */
    virtual void left(float speed, float radius, float angle) = 0;

    /**
     * @brief Moves the robot in a curve to the right.
     *
     * @param speed - The speed of the robot in percentage.
     * @param radius - The radius of the curve in centimeters.
     * @param angle - The angle of the curve in degrees.
     */
    virtual void right(float speed, float radius, float angle) = 0;

    /**
     * @brief Calibrates the direction of the robot in a straight line.
     */
    virtual void directionLineCalibration() = 0;

    /**
     * @brief Calibrates the direction of the robot in a curve.
     */
    virtual void directionCurveCalibration() = 0;

    /**
     * @brief Makes the robot stop.
     */
    void stop();

    /**
     * @brief Makes the robot slow down to a stop.
     */
    void slow();

    /**
     * @brief Makes the robot block the motors.
     */
    void block();

    /**
     * @brief Resets the movement counters.
     */
    void reset();

    /**
     * @brief Returns the track of the robot.
     *
     * @return float - The track of the robot in centimeters.
     */
    float getTrack();

    /**
     * @brief Returns the array of motors.
     */
    Motor *getMotors();

protected:
    Motor *_motors;           // Array of motors
    int _numMotors;           // Number of motors
    int _MIN_PWM = 2048;      // Minimum PWM value
    int _MAX_PWM = 4095;      // Maximum PWM value
    float _MIN_SPEED = 50.0;  // Minimum speed in percentage
    float _MAX_SPEED = 100.0; // Maximum speed in percentage

private:
    float _track; // Distance between wheels (cm)
};
#endif
