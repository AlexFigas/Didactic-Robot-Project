/*
 * Expander.h - Library for controlling a PWM expander.
 *
 * Written by Alexandre Figueiredo and Daniela Gonçalves
 */

#ifndef EXPANDER_H
#define EXPANDER_H

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

/*
 * Class representing a PWM expander.
 */
class Expander
{
public:
    // Public constants

    // Public variables

    // Public methods

    /*
     * Constructor for the Expander class.
     *
     * @param address - An optional byte indicating the I2C address of the expander.
     *                  Defaults to 0x40.
     */
    Expander(byte address = 0x40);

    /*
     * Initializes the expander.
     * This method should be called once at the beginning of the program.
     */
    void begin();

    /*
     * Sets the duty cycle of a PWM channel on the expander.
     *
     * @param channel - A byte indicating the channel number to set the duty cycle for.
     * @param duty_cycle - A byte indicating the duty cycle to set.
     *                     Must be between 0 and 100.
     */
    void setDutyCycle(byte channel, int duty_cycle, bool digital = false);

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
