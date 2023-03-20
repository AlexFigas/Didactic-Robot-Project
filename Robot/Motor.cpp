#include "Motor.h"

Motor::Motor(Expander expander, MotorController controller)
{
    _expander = expander;
    _controller = controller;
    _counter = 0;
}

void Motor::begin()
{
    // Set initial direction
    _expander.begin();
    _expander.setDutyCycle(_controller.PIN_EN, 0);
    setDirection(true);

    pinMode(_controller.interrupt.PIN_DO, INPUT_PULLUP);

    // TODO: Finish no interrupt implementation
    // If the motor has an interrupt
    if (_controller.interrupt.PIN_DO != 0 && _controller.interrupt.INT_COUNT != 0)
    {
        attachInterrupt(digitalPinToInterrupt(_controller.interrupt.PIN_DO), std::bind(&Motor::_incrementCounter, this), RISING);
    }
}

void Motor::setDirection(bool clockwise)
{
    if (clockwise)
    {
        _expander.setDutyCycle(_controller.PIN_IN1, _FULL_SPEED); // Cloclwise
        _expander.setDutyCycle(_controller.PIN_IN2, _STOP_SPEED); // Counterclockwise
    }
    else
    {
        _expander.setDutyCycle(_controller.PIN_IN1, _STOP_SPEED); // Cloclwise
        _expander.setDutyCycle(_controller.PIN_IN2, _FULL_SPEED); // Counterclockwise
    }
}

void Motor::front(int speed) // TODO: Implement cm
{
    resetCounter();
    setDirection(true);
    _expander.setDutyCycle(_controller.PIN_EN, speed);
}

void Motor::back(int speed) // TODO: Implement cm
{
    resetCounter();
    setDirection(false);
    _expander.setDutyCycle(_controller.PIN_EN, speed);
}

void Motor::stop(bool now)
{
    if (now)
    {
        _expander.setDutyCycle(_controller.PIN_EN, _FULL_SPEED);
        _expander.setDutyCycle(_controller.PIN_IN1, _FULL_SPEED);
        _expander.setDutyCycle(_controller.PIN_IN2, _FULL_SPEED);
    }
    else
    {
        _expander.setDutyCycle(_controller.PIN_EN, _STOP_SPEED);
        _expander.setDutyCycle(_controller.PIN_IN1, _STOP_SPEED);
        _expander.setDutyCycle(_controller.PIN_IN2, _STOP_SPEED);
    }
}

void Motor::_incrementCounter()
{
    ++_counter;
}

int Motor::getCounter()
{
    return _counter;
}

void Motor::resetCounter()
{
    _counter = 0;
}
