#include "Robot.h"

BluetoothSerial _serialBT; 

Robot::Robot(String name, Movement* movement)
{
    _name = name;
    _movement = movement;
    _command = "";
}

void Robot::begin()
{
    // Bluetooth communication
    _serialBT.begin(_name);
    _movement->begin();
}

void Robot::loop()
{
    // Receiving bluetooth messages
    if (_serialBT.available())
    {
        _command = _serialBT.readStringUntil('\n');
        _processCommand(_command);
        _command = "";
    }
}

void Robot::_processCommand(String msg)
{
    // First char - type of movement
    char movementType = msg.charAt(0);

    // Check if the movement is valid
    if (movementType == 'f' || movementType == 'b' || movementType == 'l' || movementType == 'r')
    {

        // Commas separator
        int separator1 = msg.indexOf(',');
        int separator2 = msg.indexOf(',', separator1 + 1);

        if (separator1 != -1 && separator2 != -1)
        {

            // Speed and first parameter
            int speed = msg.substring(separator1 + 1, separator2).toInt();
            float length = msg.substring(separator2 + 1).toFloat();

            // Forward
            if (movementType == 'f')
            {
                _movement->line(speed, length, true);
            }
            // Backward
            else if (movementType == 'b')
            {
                _movement->line(speed, length, false);
            }
            // Curve
            else if (movementType == 'l' || movementType == 'r')
            {
                int separator3 = msg.indexOf(',', separator2 + 1);

                if (separator3 != -1)
                {
                    // Radius and Angle
                    int radius = msg.substring(separator2 + 1, separator3).toInt();
                    int angle = msg.substring(separator3 + 1).toInt();

                    // Left turn
                    if (movementType == 'l')
                    {
                        _movement->curve(speed, radius, angle, true);
                    }
                    // Right turn
                    else if (movementType == 'r')
                    {
                        _movement->curve(speed, radius, angle, false);
                    }
                }
            }
        }
    }
}
