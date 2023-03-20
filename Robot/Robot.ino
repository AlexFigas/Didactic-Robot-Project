#include "Motor.h"

Expander expander = Expander();

// MotorController controller1 = MotorController{
//     .PIN_EN = 0,
//     .PIN_IN1 = 1,
//     .PIN_IN2 = 2,
//     .interrupt = Interrupt{
//         .PIN_DO = 2,
//         .INT_COUNT = 20,
//     },
// };
// Motor motor2 = Motor(expander, controller1);

MotorController controller2 = MotorController{
    .PIN_EN = 5,
    .PIN_IN1 = 3,
    .PIN_IN2 = 4,
    .interrupt = Interrupt{
        .PIN_DO = 4,
        .INT_COUNT = 20,
    },
};
Motor motor1 = Motor(expander, controller2);

void setup()
{
    Serial.begin(9600);

    motor1.begin();

    motor1.front(100);
    // motor2.begin();
    // motor2.front(20, 100);
    // motor2.front(20, 10);
}

void loop()
{
    Serial.println("Counter: " + String(motor1.getCounter()));

    if (motor1.getCounter() >= 20) // LED
    {
        motor1.stop(false);
    }

    // if (motor2.getCounter() >= 20) //MOTOR
    // {
    //     motor2.stop();
    // }
}