#include "Motor.h"

Motor::Motor(byte id, Expander expander, MotorController controller)
{
    _expander = expander;
    _controller = controller;
    _id = id;
}

void Motor::incrementCount()
{
    Motor::_motorCounters[_id]++;
}

int Motor::getCount()
{
    return Motor::_motorCounters[_id];
}

void Motor::begin()
{
    // Set initial direction
    _expander.begin();
    _expander.setDutyCycle(_controller.PIN_EN, 0);
    setDirection(true);


    // If the motor has an interrupt
    if (_controller.interrupt.PIN_DO != 0 && _controller.interrupt.INT_COUNT != 0)
    {

        // Assign current instance to pointer
        pinMode(_controller.interrupt.PIN_DO, INPUT);

        // FIXME: This is not working
        // Motor *pointer = this;
        // attachInterrupt(
        //     digitalPinToInterrupt(_controller.interrupt.PIN_DO),
        //     []() -> void {
        //         pointer->incrementCount();
        //     },
        //     RISING);

        attachInterrupt(
            digitalPinToInterrupt(_controller.interrupt.PIN_DO),
            []() -> void {
                Motor::_motorCounters[_id]++;
            },
            RISING);
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

void Motor::front(int cm)
{
    count = 0;
    setDirection(true);
    _expander.setDutyCycle(_controller.PIN_EN, 100);
    _computeInterruptDistance(cm);
}

void Motor::back(int cm)
{
    count = 0;
    setDirection(false);
    _expander.setDutyCycle(_controller.PIN_EN, 100);
    _computeInterruptDistance(cm);
}

void Motor::_stop()
{
    _expander.setDutyCycle(_controller.PIN_EN, 0);
    _expander.setDutyCycle(_controller.PIN_IN1, 0);
    _expander.setDutyCycle(_controller.PIN_IN2, 0);
}

void Motor::_computeInterruptDistance(int cm)
{
    _interruptForDistance = (int)round(cm * _controller.interrupt.INT_COUNT / 20.42);
}
