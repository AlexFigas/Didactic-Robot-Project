#include "Motor.h"

// Pointer outside of the class
Motor *pointer;

// Define global handler
static void interruptHandler() {
  // Calls class member handler counter
  pointer->interruptCounter();
}

Motor::Motor(Expander expander, MotorController controller) {
  _expander = expander;
  _controller = controller;
}

void Motor::begin() {
  // Set initial direction
  _expander.begin();
  _expander.setDutyCycle(_controller.PIN_EN, 0);
  setDirection(true);

  // If the motor has an interrupt
  if (_controller.interrupt.PIN_DO != 0 || _controller.interrupt.INT_COUNT != 0) {

    // Assign current instance to pointer
    pointer = this;
    pinMode(_controller.interrupt.PIN_DO, INPUT);
    attachInterrupt(digitalPinToInterrupt(_controller.interrupt.PIN_DO), interruptHandler, RISING);
  }
}

void Motor::setDirection(bool clockwise) {
  if (clockwise) {
    _expander.setDutyCycle(_controller.PIN_IN1, 100);  // Cloclwise
    _expander.setDutyCycle(_controller.PIN_IN2, 0);    // Counterclockwise
  } else {
    _expander.setDutyCycle(_controller.PIN_IN1, 0);    // Cloclwise
    _expander.setDutyCycle(_controller.PIN_IN2, 100);  // Counterclockwise
  }
}

// TODO - raio, wheel size e interrupt (pode ter ou não ter)
void Motor::front(int cm) {
  // 6.5 cm de diâmetro
  // 1 volta = 20.5 cm
}

void Motor::back(int cm) {
}

void Motor::interruptCounter() {
  _counter++;
}
