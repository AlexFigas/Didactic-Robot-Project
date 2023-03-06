#include <BluetoothSerial.h>
#include <Wire.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Instance of the BluetoothSerial class
BluetoothSerial SerialBT;

// Define the address of the PCF8574
#define PCF8574_ADDR 0x20

// Define the control pins of the motor module
#define ENA 1
#define IN1 2
#define IN2 3
#define ENB 4
#define IN3 5
#define IN4 6

// Define I2C pins
#define I2C_SDA 21
#define I2C_SCL 22

String msg = "";

void setup() {
  // Serial and Serial Bluetooth initialization
  Serial.begin(115200);
  SerialBT.begin("Robot");

  // Initialize communication with the PCF8574
  Wire.begin(I2C_SDA, I2C_SCL);

  // Set the control bits of the PCF8574 as outputs
  Wire.beginTransmission(PCF8574_ADDR);
  Wire.write(0x00); // Set all bits as outputs
  Wire.endTransmission();
}

void loop() {

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  // Testing turn on led when receive message
  if (SerialBT.available()) {
    msg = SerialBT.readString();
    Serial.print(msg);

    Wire.beginTransmission(PCF8574_ADDR);
    Wire.write(0b00000010); 
    Wire.endTransmission();

    msg = "";
  }

  delay(20);
}