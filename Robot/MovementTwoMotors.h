/**
 * @file MovementTwoMotors.h - Library for controlling the movement of a robot with two motors.
 *
 * @author Alexandre Figueiredo and Daniela Gonçalves
 */

#ifndef MOVEMENTTWOMOTORS_H
#define MOVEMENTTWOMOTORS_H

#include "Movement.h"
#include <iostream>
#include <cmath>

/**
 * @brief Class representing the movement of a robot with two motors.
 *
 * This class is responsible for controlling the movement of a robot with two motors.
 * It uses the Motor class to control the motors.
 */
class MovementTwoMotors : public Movement
{
public:
    /**
     * @brief Construct a new MovementTwoMotors object
     *
     * @param motors - An array of Motor objects.
     * @param track - The track of the robot in centimeters.
     */
    MovementTwoMotors(Motor *motors, float track);

    /**
     * @brief Moves the robot in a curve.
     *
     * @param speed - The speed of the robot in percentage.
     * @param radius - The radius of the curve in centimeters.
     * @param angle - The angle of the curve in degrees.
     * @param isLeft - The direction of the curve. True for left, false for right.
     */
    void curve(float speed, float radius, float angle, bool isLeft = true) override;

    /**
     * @brief Moves the robot to the left.
     *
     * @param speed - The speed of the robot in percentage.
     * @param radius - The radius of the curve in centimeters.
     * @param angle - The angle of the curve in degrees.
     */
    void left(float speed, float radius, float angle) override;

    /**
     * @brief Moves the robot to the right.
     *
     * @param speed - The speed of the robot in percentage.
     * @param radius - The radius of the curve in centimeters.
     * @param angle - The angle of the curve in degrees.
     */
    void right(float speed, float radius, float angle) override;

    /**
     * @brief Calibrates the direction of the curve.
     */
    void directionCurveCalibration() override;

    /**
     * @brief Calibrates the direction of the straight line.
     */
    void directionLineCalibration() override;

private:
};

#endif
