#include "MovementTwoMotors.h"
#include "Robot.h"

Expander expander = Expander();

MotorController leftController = MotorController{
    .PIN_EN = 3,
    .PIN_IN1 = 4,
    .PIN_IN2 = 5,
    .interrupt = Interrupt{
        .PIN_DO = 33,
        .INT_COUNT = 20},
    .wheelRadius = 3.3};

MotorController rightController = MotorController{
    .PIN_EN = 0,
    .PIN_IN1 = 1,
    .PIN_IN2 = 2,
    .interrupt = Interrupt{
        .PIN_DO = 32,
        .INT_COUNT = 20},
    .wheelRadius = 3.3};

float track = 13.0;
MovementTwoMotors movement = MovementTwoMotors(new Motor[2]{Motor(expander, leftController), Motor(expander, rightController)}, track);

String name = "Robot";
Robot robot = Robot(name, &movement);

void setup()
{
    robot.begin();
}

void loop()
{
    robot.loop();
}