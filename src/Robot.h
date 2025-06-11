/**
 * @file Robot.h - Library for controlling the robot.
 *
 * @author Alexandre Figueiredo and Daniela Gonçalves
 */

#ifndef ROBOT_H
#define ROBOT_H
#include "Movement.h"
#include <Arduino.h>
#include <BluetoothSerial.h>

class Robot
{
  public:
    Robot(String name, Movement* movement);

    // Public constants

    // Public variables

    // Public methods
    virtual void begin();
    void loop();

  protected:
    // Protected constants

    // Protected variables
    Movement* _movement;

    // Protected methods

  private:
    // Private constants

    // Private variables
    String _name;
    String _command;

    // Private methods
    void _processCommand(String command);
};
#endif