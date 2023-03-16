#include "Motor.h"

Motor::Motor(Expander expander, MotorController controller)
{
    _expander = expander;
    _controller = controller;
}

void Motor::incrementCount()
{
    ++_count;
}

int Motor::getCount()
{
    return _count;
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

        // TODO: This is not working
        // pinMode(_controller.interrupt.PIN_DO, INPUT);
        // attachInterrupt(
        //     digitalPinToInterrupt(_controller.interrupt.PIN_DO),
        //     incrementCount,
        //     RISING);

        // Motor *pointer = this;
        // attachInterrupt(
        //     digitalPinToInterrupt(_controller.interrupt.PIN_DO),
        //     []() -> void {
        //         pointer->incrementCount();
        //     },
        //     RISING);

        // attachInterrupt(
        //     digitalPinToInterrupt(_controller.interrupt.PIN_DO),
        //     []() -> void {
        //         Motor::_motorCounters[id]++;
        //     },
        //     RISING);

        /* 
            Já foi testado com:
            Variável estática
            Variável estática com ponteiro
            
         */
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
    _count = 0;
    setDirection(true);
    _expander.setDutyCycle(_controller.PIN_EN, 100);
    _computeInterruptDistance(cm);
}

void Motor::back(int cm)
{
    _count = 0;
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
