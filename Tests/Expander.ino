#include <Wire.h>

#define PCF8574_ADDR 0x20 // Expansor address
#define SDA 21            // SDA pin
#define SCL 22            // SCL pin

void setup()
{
    Wire.begin(SDA, SCL); // Communication initialization

    Wire.beginTransmission(PCF8574_ADDR); // Begin transmission
    Wire.write(0x1);                      // Message
    Wire.endTransmission();               // End transmission
}