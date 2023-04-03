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

    _hasInterrupt = _controller.interrupt.INT_COUNT > 0;
    // If the motor has an interrupt
    if (_hasInterrupt)
    {
        pinMode(_controller.interrupt.PIN_DO, INPUT_PULLUP);
        attachInterrupt(digitalPinToInterrupt(_controller.interrupt.PIN_DO), std::bind(&Motor::_incrementCounter, this), CHANGE);
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

void Motor::front(int speed, float cm)
{
    if (_hasInterrupt && cm > 0)
    {
        resetCounter();
        _cmToInterruptCount(cm, _controller.wheelDiameter);
    }
    setDirection(true);
    setSpeed(speed);
}

void Motor::back(int speed, float cm)
{
    if (_hasInterrupt && cm > 0)
    {
        resetCounter();
        _cmToInterruptCount(cm, _controller.wheelDiameter);
    }
    setDirection(false);
    setSpeed(speed);
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

int Motor::getCounter() // TODO: depois apagar, só para testar
{
    return _counter;
}

void Motor::resetCounter()
{
    _counter = 0;
}

void Motor::setSpeed(int speed)
{
    _expander.setDutyCycle(_controller.PIN_EN, speed);
}

void Motor::_cmToInterruptCount(float cm, int wheelDiameter)
{
    float perimeter = wheelDiameter * PI;
    float rotations = cm / perimeter;
    _interruptCount = floor(rotations * (_controller.interrupt.INT_COUNT * 2));
}
