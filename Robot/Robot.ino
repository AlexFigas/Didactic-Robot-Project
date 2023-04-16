#include "MovementTwoMotors.h"

Expander expander = Expander();

MotorController leftController = MotorController{
    .PIN_EN = 3,
    .PIN_IN1 = 4,
    .PIN_IN2 = 5,
    .interrupt = Interrupt{
        .PIN_DO = 32,
        .INT_COUNT = 20
    },
    .wheelRadius = 3
};
Motor left = Motor(expander, leftController);

MotorController rightController = MotorController{
    .PIN_EN = 0,
    .PIN_IN1 = 1,
    .PIN_IN2 = 2,
    .interrupt = Interrupt{
        .PIN_DO = 32,
        .INT_COUNT = 20
    },
    .wheelRadius = 3
};
Motor right = Motor(expander, rightController);

float wheelbase = 13.0;
float wheelRadius = 3.0;
MovementTwoMotors movement = MovementTwoMotors(new Motor[2]{left, right}, wheelbase, wheelRadius);

void setup()
{
    Serial.begin(9600);
    
    delay(1000);

    movement.begin();
    movement.left(20, 360, 50);
    //movement.front(50, 40);
}

void loop()
{
    /*if (right.getCounter() >= 40 || left.getCounter() >= 40)
    {
        right.stop(true);
        left.stop(true);
    }*/
}
