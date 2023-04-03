#include "Motor.h"

Expander expander = Expander();

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

void setup()
{
    right.begin();
    left.begin();

    right.front(100);
    delay(50);
    left.front(100);
}

void loop()
{
    if (right.getCounter() >= 40 || left.getCounter() >= 40)
    {
        right.stop(true);
        left.stop(true);
    }
}
