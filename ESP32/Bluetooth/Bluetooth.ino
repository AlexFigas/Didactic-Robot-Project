#include <BluetoothSerial.h>
#include <Wire.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Instance of the BluetoothSerial class
BluetoothSerial SerialBT;

// Define the address of the PCF8574
#define PCF8574_ADDR 0x20

// Define the control bits of the motor module
#define ENA 1
#define IN1 2
#define IN2 3
#define ENB 4
#define IN3 5
#define IN4 6

String msg = "";

void setup() {
  // Serial and Serial Bluetooth initialization
  Serial.begin(115200);
  SerialBT.begin("Robot");

  // Initialize communication with the PCF8574
  Wire.begin();

  // Set the control bits of the PCF8574 as outputs
  Wire.beginTransmission(PCF8574_ADDR);
  Wire.write(0x00); // Set all bits as outputs
  Wire.endTransmission();
}

void loop() {

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }

  if (SerialBT.available()) {
    msg = SerialBT.readString();
    Serial.print(msg);

    // TODO
    if (msg.compareTo("m") == 0) {
        Serial.println("Starting...");
        // Rotate motor A and B clockwise
        Wire.beginTransmission(PCF8574_ADDR);
        Wire.write(0b00000110);
        Wire.endTransmission();
    }
    msg = "";
  }
  delay(20);
}