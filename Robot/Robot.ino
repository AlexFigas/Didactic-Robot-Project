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

#define NMOTORS 2

class PID {
    private:
        float kp, kd, ki, umax; // Parameters
        float eprev, eintegral; // Storage

    public:
    PID() : kp(1), kd(0.0025), ki(0), umax(60.0), eprev(0.0), eintegral(0.0){}

    void setParams(float kpIn, float kdIn, float kiIn, float umaxIn) {
        kp = kpIn; kd = kdIn; ki = kiIn; umax = umaxIn;
    }

    void evalu(int value, int target, float deltaT, int &pwr, int &dir) {

        // Calcular o erro
        int error = target - value;

        // Derivada
        float dedt = (error - eprev) / (deltaT);

        // Integral 
        eintegral = eintegral + error * deltaT;

        // Sinal de controlo
        float u = kp * error + kd * dedt + ki * eintegral;
        pwr = (float) fabs(u);

        // Limitar à velocidade máxima
        if (pwr > umax) {
            pwr = umax;
        }

        // Definir a direção
        dir = 1;
        if (u < 0) {
            dir = -1;
        }

        eprev = error;
    }
};

// Pins
const int IN1[] = {4, 1};
const int IN2[] = {5, 2};

// Globals
long prevT = 0;
volatile int posi[] = {0, 0};

PID pid[NMOTORS];

void setup()
{
    command = "";

    // Serial and Bluetooth communication
    Serial.begin(9600);
    SerialBT.begin("Robot");
     
    movement.begin();
}

float target_f[] = {0.0, 0.0};
long target[] = {300, 300};

void loop()
{
    /*// Receiving bluetooth messages
    if ( SerialBT.available() ) 
    {
        command = SerialBT.readStringUntil('\n'); 
        processMessage(command);
        command = "";
    }*/

    // Quando chegar ao objetivo (target ticks)
    while(true) {

        posi[0] = movement.getMotors()[0].getCounter();
        posi[1] = movement.getMotors()[1].getCounter();

        if (posi[0] > target[0] || posi[1] > target[1]) {
            break;
        }

        // Tempo e deltaT
        long currT = micros();
        float deltaT = ((float) (currT - prevT)) / (1.0e6);
        prevT = currT;

        // Desativar interrupts temporariamente durante a leitura
        int pos[2];
        noInterrupts();
        for(int k = 0; k < NMOTORS; k++) {
            pos[k] = posi[k];
        }
        interrupts();

        // Calcular o sinal de controlo para os motores e definir PWM
        for(int k = 0; k < NMOTORS; k++) {

          int pwm, dir;
          pid[k].evalu(pos[k], target[k], deltaT, pwm, dir);
          setMotor(k, dir, pwm, IN1[k], IN2[k]);
        }

        Serial.print(posi[0]);
        Serial.print(" ");
        Serial.print(posi[1]);
        Serial.println("");

        /*for(int k = 0; k < NMOTORS; k++){
            Serial.print(target[k]);
            Serial.print(" ");
            Serial.print(pos[k]);
            Serial.print(" ");
        }
        Serial.println();
        */
      }

      // Quando terminar para
      movement.stop(true);
}

void setMotor(int index, int dir, float pwmVal, int in1, int in2) {

    movement.getMotors()[index].setSpeed(pwmVal);
    
    // Em frente
    if(dir == 1) {
        movement.getMotors()[index].setDirection(true);
    }
    // Para trás
    else if(dir == -1) {
        movement.getMotors()[index].stop(false);
        //movement.getMotors()[index].setDirection(false);
    }
    // Parar
    else {
        movement.getMotors()[index].stop(true);
    }  
}

void processMessage(String msg) {

    // First char - type of movement
    char movementType = msg.charAt(0);

    // Check if the movement is valid
    if (movementType == 'f' || movementType == 'b' || movementType == 'l' || movementType == 'r') {

        // Commas separator
        int separator1 = msg.indexOf(',');
        int separator2 = msg.indexOf(',' , separator1 + 1);
        
        if (separator1 != -1 && separator2 != -1)
        {
            int separator3 = msg.indexOf(',', separator2 + 1);

            // Speed and first parameter
            int speed = msg.substring(separator1 + 1, separator2).toInt(); 
            float length = msg.substring(separator2 + 1, separator3).toFloat();
            float offset = msg.substring(separator3 + 1).toFloat();
            
            // Forward
            if (movementType == 'f')
            {
                movement.getMotors()[1].setOffset(offset);
                movement.line(speed, length, true);

                SerialBT.println(movement.resultLeft);
                SerialBT.println("-------------");
                SerialBT.println(movement.resultRight);                
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
