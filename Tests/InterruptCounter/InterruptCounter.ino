#include "MovementTwoMotors.h"

Expander expander = Expander();

MotorController leftController = MotorController{
    .PIN_EN = 3,
    .PIN_IN1 = 4,
    .PIN_IN2 = 5,
    .interrupt = Interrupt{
        .PIN_DO = 33,
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

float track = 13.0;
float wheelRadius = 3.0;
MovementTwoMotors movement = MovementTwoMotors(new Motor[2]{left, right}, track, wheelRadius);

void setup()
{
    Serial.begin(9600);
    
    delay(1000);

    movement.begin();

    for (int i = 50; i <= 100; i+=10) {

        for (int t = 0; t < 2; t++) {

          Serial.print("Teste ");
          Serial.println(t+1);
          movement.front(i, 100.0);
          delay(10000);
          movement.stop(true);
          delay(3000);

          Serial.print(" Velocidade: ");
          Serial.print(i);
          Serial.print(" - Roda esquerda: ");
          Serial.print(movement.getMotors()[0].getCounter());
          Serial.print(" - Roda direita: ");
          Serial.print(movement.getMotors()[1].getCounter());
          Serial.println("");
          Serial.println("------------------------------------------");

          movement.reset();
        } 
    }
}

void loop()
{
}
