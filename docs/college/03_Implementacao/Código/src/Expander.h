/**
 * @file Expander.h - Library for controlling a PWM expander.
 *
 * @author Alexandre Figueiredo and Daniela Gonçalves
 */

#ifndef EXPANDER_H
#define EXPANDER_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

/**
 * @brief Class representing a PWM expander.
 */
class Expander
{
public:
    // Public constants

    // Public variables

    // Public methods

    /**
     * @brief Constructor for the Expander class.
     *
     * @param address - An optional byte indicating the I2C address of the expander.
     *                  Defaults to 0x40.
     */
    Expander(byte address = 0x40);

    /**
     * @brief Initializes the expander.
     * This method should be called once at the beginning of the program.
     */
    void begin();

    /**
     * @brief Sets the duty cycle of a PWM channel on the expander.
     *
     * @param channel - A byte indicating the channel number to set the duty cycle for.
     * @param duty_cycle - A byte indicating the duty cycle to set.
     *                     Must be between 0 and 100.
     */
    int setDutyCycle(byte channel, float duty_cycle);

    /**
     * @brief Sets the PWM value of a PWM channel on the expander.
     *
     * @param channel - A byte indicating the channel number to set the PWM value for.
     * @param pwm - An int indicating the PWM value to set.
     */
    void setPWM(byte channel, int pwm);

private:
    // Private constants
    const static byte _MAX_DUTY_CYCLE = 100; // The maximum duty cycle value
    const static byte _MIN_DUTY_CYCLE = 0;   // The minimum duty cycle value
    const static int _MAX_PWM_ON = 4095;     // The maximum PWM on point value
    const static int _MIN_PWM_ON = 0;        // The minimum PWM on point value
    const static int _PWM_OFF_POINT = 0;     // The PWM off point value

    // Private variables
    byte _address;                  // The I2C address of the expander
    Adafruit_PWMServoDriver _board; // The Adafruit_PWMServoDriver object for controlling the expander
    bool _initialized;              // A boolean indicating whether the expander has been initialized

    // Private methods
};

#endif
