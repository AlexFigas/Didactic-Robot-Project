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

void processCommand(String cmd) {
    int speed = cmd.toInt();
    
    //movement.line(speed, 100.0);
    right.front( speed, 100 );

    unsigned long finalTime = millis()+10000;

    while ( millis()<finalTime ) 
      ;

    movement.slow();
    movement.block();    
        
    char stringByte[80];
    Motor * motors = movement.getMotors();

    while ( millis()< (finalTime+1000) ) 
      ;

    sprintf(stringByte, "%d;%d", motors[0].getCounter(), motors[1].getCounter() );

    SerialBT.println( stringByte );

    movement.reset();
}

void setup()
{
    Serial.begin(9600);
    command = "";
    movement.begin();
    SerialBT.begin("Robot"); // Serial Bluetooth initialization

/*
    movement.begin();
    movement.line(25.0, 100.0);
    delay(5000);
    movement.line(50.0, 100.0);
    delay(5000);
    movement.line(25.0, 100.0, false);
    delay(5000);
    movement.line(50.0, 100.0, false);
    */
}

void loop()
{
    // Ao receber algo pelo bluetooth
    if (SerialBT.available()) 
    {
        command = SerialBT.readStringUntil('\n');
        processCommand( command );
        command = "";

        /*if ( currentChar=='\n' ) {
            processCommand( command );
            command = "";
        }
        else {
            command += currentChar;
        }*/
    }

  /*if ( Serial.available() ) {
    char currentChar = (char)Serial.read();

    if ( currentChar=='\n' ) {
      processCommand( command );
      command = "";
    }
    else {
      command += currentChar;
    }
  }*/
}
