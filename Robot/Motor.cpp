#include "Motor.h"

Motor::Motor(Expander expander, MotorController controller)
{
    _expander = expander;
    _controller = controller;
    direction = true;

    _radius = _controller.wheelRadius;
    _perimeter = 21.5; //2 * _controller.wheelRadius * PI;

    _turnInterruptCount = _controller.interrupt.INT_COUNT * _INTERRUPT_FIX;
    _counter = 0;
    _speed = 0.0;
    _offset = 0.0;
    _pwm = 0;
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
        direction = true;
        _expander.setDutyCycle(_controller.PIN_IN1, _FULL_SPEED); // Clockwise
        _expander.setDutyCycle(_controller.PIN_IN2, _STOP_SPEED); // Counterclockwise
    }
    else
    {
        direction = false;
        _expander.setDutyCycle(_controller.PIN_IN1, _STOP_SPEED); // Clockwise
        _expander.setDutyCycle(_controller.PIN_IN2, _FULL_SPEED); // Counterclockwise
    }
}

void Motor::front(float speed, float length)
{
    if (_hasInterrupt && length > 0)
    {    
        resetCounter();
        _updateInterruptTarget(length);
    }
    setDirection(true);
    setSpeed(speed);
}

void Motor::back(float speed, float length)
{
    if (_hasInterrupt && length > 0)
    {    
        resetCounter();
        _updateInterruptTarget(length);
    }
    setDirection(false);
    setSpeed(speed);
}

void Motor::slow()
{
    _expander.setDutyCycle(_controller.PIN_EN, _STOP_SPEED);
}

void Motor::block()
{
    _expander.setDutyCycle(_controller.PIN_IN1, _FULL_SPEED);
    _expander.setDutyCycle(_controller.PIN_IN2, _FULL_SPEED);
}

void Motor::stop(bool now)
{
    if (now)
    {
        slow();
        block();
    }
    else
    {
        slow();
    }
}

void Motor::_incrementCounter()
{
    // TODO

    if (direction == true) 
    {
        ++_counter;
    }
    else {
        --_counter;
    }
}

int Motor::getCounter() // TODO: depois apagar, só para testar
{
    if (_hasInterrupt)
        return _counter;
    else
        return 0;
}

void Motor::resetCounter()
{
    _counter = 0;
}

float Motor::getOffset()
{
    return _offset;
}

void Motor::setOffset(float offset)
{
    _offset = offset;
}

void Motor::setSpeed(float speed)
{ 
    float speedOffset = speed + _offset;
    _speed = speedOffset > 100.0 ? 100.0 : (speedOffset < 50.0 ? 50.0 : speedOffset);
    _pwm = _expander.setDutyCycle(_controller.PIN_EN, _speed);
}

void Motor::setPWM(int pwm)
{
    _pwm = pwm;
    _expander.setPWM(_controller.PIN_EN, _pwm);
}

int Motor::getPWM()
{
    return _pwm;
}

float Motor::getSpeed()
{
    return _speed;
}

bool Motor::hasInterrupt()
{
    return _hasInterrupt;
}

int Motor::getTargetInterrupt()
{
    return _interruptTarget;
}

float Motor::getPerimeter()
{
    return _perimeter;
}

float Motor::getRadius()
{
    return _radius;
}

void Motor::_updateInterruptTarget(float length)
{
    // Wheel rotations 
    float rotations = length / _perimeter;

    // Number of interrupts required
    _interruptTarget = floor(rotations * _turnInterruptCount);
}
