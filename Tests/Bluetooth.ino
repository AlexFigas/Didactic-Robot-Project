#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);    // Serial initialization
    SerialBT.begin("Robot"); // Serial Bluetooth initialization
}

void loop()
{
    if (Serial.available()) // If the user sends message
    {
        SerialBT.write(Serial.read()); // Send it via bluetooth
    }
    if (SerialBT.available()) // If the user receives message
    {
        Serial.write(SerialBT.read()); // Receive it serial monitor
    }
}