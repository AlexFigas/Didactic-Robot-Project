#include "MovementTwoMotors.h"
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

Expander expander = Expander();

MotorController leftController = MotorController{
    .PIN_EN = 3,
    .PIN_IN1 = 4,
    .PIN_IN2 = 5,
    .interrupt = Interrupt{
        .PIN_DO = 33,
        .INT_COUNT = 20
    },
    .wheelRadius = 3.3
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
    .wheelRadius = 3.3
};
Motor right = Motor(expander, rightController);

float track = 13.0;
float wheelRadius = 3.0;
MovementTwoMotors movement = MovementTwoMotors(new Motor[2]{left, right}, track, wheelRadius);

String command;

/*
void processCommand(String cmd) {

    int speed = cmd.toInt();
    
    movement.line(speed, 100.0);
    unsigned long finalTime = millis()+5000;

    while ( millis()<finalTime ) 
      ;

    movement.slow();
    movement.block();    
        
    char stringByte[80];
    Motor * motors = movement.getMotors();

    while ( millis()< (finalTime+250) ) 
      ;

    sprintf(stringByte, "%d;%d", motors[0].getCounter(), motors[1].getCounter() );
    SerialBT.println( stringByte );

    movement.reset();
}*/

void setup()
{
    command = "";

    // Serial and Bluetooth communication
    Serial.begin(9600);
    SerialBT.begin("Robot"); 
    movement.begin();
}

void loop()
{
    // Receiving bluetooth messages
    if (SerialBT.available()) 
    {
        command = SerialBT.readStringUntil('\n');
        processMessage(command);
        command = "";
    }
}

void processMessage(String msg) {

    // First char - type of movement
    char movementType = msg.charAt(0);

    // Check if the movement is valid
    if (movementType == 'f' || movementType == 'b' || movementType == 'l' || movementType == 'r') {

        // Commas separator
        int separator1 = msg.indexOf(',');
        int separator2 = msg.indexOf(',', separator1 + 1);
        
        if (separator1 != -1 && separator2 != -1)
        {
            // Speed and first parameter
            int speed = msg.substring(separator1 + 1, separator2).toInt(); 
            float length = msg.substring(separator2 + 1).toFloat();
            
            // Forward
            if (movementType == 'f')
            {
                movement.line(speed, length, true);

                /*
                // Comentar as linhas 45, 48, 49 e 50 para realizar o seguinte teste de 5 segundos                 
                //  DEBUG - Num de ticks //
                unsigned long finalTime = millis()+5000;
                while (millis() < finalTime);

                movement.slow();
                movement.block();    
                    
                char stringByte[80];
                Motor* motors = movement.getMotors();

                while (millis() < (finalTime + 150));

                sprintf(stringByte, "%d;%d", motors[0].getCounter(), motors[1].getCounter() );
                SerialBT.println( stringByte );

                movement.reset();
                //  DEBUG - Num de ticks //
                */
            } 
            // Backward
            else if (movementType == 'b')
            {
                movement.line(speed, length, false);
            }
            // Curve
            else if (movementType == 'l' || movementType == 'r')
            {
                int separator3 = msg.indexOf(',', separator2 + 1);

                if (separator3 != -1) {

                    // Radius and Angle
                    int radius = msg.substring(separator2 + 1, separator3).toInt();
                    int angle = msg.substring(separator3 + 1).toInt();
                
                    // Left turn
                    if (movementType == 'l')
                    {
                        movement.curve(speed, radius, angle, true);                        
                    }
                    // Right turn
                    else if (movementType == 'r')
                    {
                        movement.curve(speed, radius, angle, false);
                    }
                }
            }
        }
    }
}
