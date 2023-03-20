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
        _expander.setDutyCycle(_controller.PIN_IN1, 100); // Cloclwise
        _expander.setDutyCycle(_controller.PIN_IN2, 0);   // Counterclockwise
    }
    else
    {
        _expander.setDutyCycle(_controller.PIN_IN1, 0);   // Cloclwise
        _expander.setDutyCycle(_controller.PIN_IN2, 100); // Counterclockwise
    }
}

void Motor::front(int speed) // TODO: Implement cm
{
    resetCounter();
    setDirection(true);
    _expander.setDutyCycle(_controller.PIN_EN, speed);
}

void Motor::back(int cm) // TODO: Implement cm
{
    resetCounter();
    setDirection(false);
    _expander.setDutyCycle(_controller.PIN_EN, 100);
}

void Motor::stop(bool now) // TODO: Implement now
{
    _expander.setDutyCycle(_controller.PIN_EN, 0);
    _expander.setDutyCycle(_controller.PIN_IN1, 0);
    _expander.setDutyCycle(_controller.PIN_IN2, 0);
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
