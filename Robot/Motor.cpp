#include "Motor.h"

Motor::Motor(Expander expander, MotorController controller)
{
    _expander = expander;
    _controller = controller;
}

void Motor::begin()
{
    _expander.begin();
    _expander.setDutyCycle(_controller.PIN_EN, 0); // Enable
    setDirection(true);

    // If the motor has an interrupt
    if (_controller.interrupt.PIN_DO != 0 || _controller.interrupt.INT_COUNT != 0)
    {
        pinMode(_controller.interrupt.PIN_DO, INPUT);
        attachInterrupt(digitalPinToInterrupt(_controller.interrupt.PIN_DO), _interruptCounter, RISING);
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

// TODO raio, wheel size e interrupt (pode ter ou não ter)
void Motor::front(int cm)
{
    // 6.5 cm de diâmetro
    // 1 volta = 20.5 cm
}

void Motor::back(int cm)
{
}

void Motor::_interruptCounter()
{
    _counter++;
}
