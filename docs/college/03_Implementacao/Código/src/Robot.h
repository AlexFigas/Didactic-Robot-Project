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
    void begin();
    void loop();

  private:
    // Private constants

    // Private variables
    Movement* _movement;
    String _name;
    String _command;

    // Private methods
    void _processCommand(String command);
};
#endif