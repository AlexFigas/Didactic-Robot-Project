#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "Expander.h"

struct MotorController
{
    byte PIN_EN;
    byte PIN_IN1;
    byte PIN_IN2;
    Interrupt interrupt;
};

struct Interrupt
{
    byte PIN_DO;
    byte INT_COUNT;
};

class Motor
{
public:
    // Constructor
    Motor(Expander expander = Expander(), MotorController controller = MotorController());

    // Methods
    void begin();
    void setDirection(bool clockwise);

    void front(int cm);
    void back(int cm);


private:
    // Variables
    Expander _expander;
    Interrupt _interrupt;
    MotorController _controller;
    int _counter = 0;

    // Methods
    void _interruptCounter();
};

#endif