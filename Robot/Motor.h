#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "Expander.h"

struct Interrupt
{
    byte PIN_DO;
    byte INT_COUNT;
};

struct MotorController
{
    byte PIN_EN;
    byte PIN_IN1;
    byte PIN_IN2;
    Interrupt interrupt;
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
    void _stop();

    void incrementCount();
    int getCount();

private:
    // Variables
    Expander _expander;
    Interrupt _interrupt;
    MotorController _controller;
    int _interruptForDistance = 0;
    int _count;
    static int _motorCounters[4];

    // Methods
    void _computeInterruptDistance(int cm);
};

#endif