#include "Motor.h"

Expander expander = Expander();

MotorController controller1 = MotorController{
    .PIN_EN = 0,
    .PIN_IN1 = 1,
    .PIN_IN2 = 2,
    .interrupt = Interrupt{
        .PIN_DO = 33,
        .INT_COUNT = 20,
    },
};
Motor m1 = Motor(expander, controller1);

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;

    m1.begin();
    m1.front(100);
}

void loop()
{
    if (m1.getCounter() >= 40)
    {
        m1.stop(true);
    }
}
