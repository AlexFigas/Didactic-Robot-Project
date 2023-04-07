#include "MovementTwoMotors.h"

Expander expander = Expander();

MotorController leftController = MotorController{
    .PIN_EN = 3,
    .PIN_IN1 = 4,
    .PIN_IN2 = 5,
    .interrupt = Interrupt{
        .PIN_DO = 32,
        .INT_COUNT = 20,
    },
};
Motor left = Motor(expander, leftController);

MotorController rightController = MotorController{
    .PIN_EN = 0,
    .PIN_IN1 = 1,
    .PIN_IN2 = 2,
    .interrupt = Interrupt{
        .PIN_DO = 33,
        .INT_COUNT = 20,
    },
};
Motor right = Motor(expander, rightController);

MovementTwoMotors movement = MovementTwoMotors(new Motor[2]{left, right}, 13);

void setup()
{
    Serial.begin(9600);
    
    delay(1000);

    movement.begin();
    movement.left(15, 90, 50);
}

void loop()
{
    /*if (right.getCounter() >= 40 || left.getCounter() >= 40)
    {
        right.stop(true);
        left.stop(true);
    }*/
}
