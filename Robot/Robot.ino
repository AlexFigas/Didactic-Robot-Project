#include "Motor.h"

MotorController controller2 = MotorController{
    .PIN_EN = 5,
    .PIN_IN1 = 3,
    .PIN_IN2 = 4,
    .interrupt = Interrupt{
        .PIN_DO = 2,
        .INT_COUNT = 20,
    },
};
Motor motor = Motor(Expander(), controller2);

void setup()
{
    motor.begin();
    motor.front(20);

}

void loop()
{
    if (motor.getC2() >= 1)
    {
        motor._stop();
    }
}