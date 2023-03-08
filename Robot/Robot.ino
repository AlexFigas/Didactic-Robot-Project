#include "Expander.h"

Expander expander;

#define ENABLE_A 0
#define IN1 1
#define IN2 2

void setup()
{
    expander.begin();
    expander.setDutyCycle(ENABLE_A, 0); // Enable
    expander.setDutyCycle(IN1, 100);    // Cloclwise
    expander.setDutyCycle(IN2, 0);      // Counterclockwise
}

void loop()
{
    // Figure out when does the motor start to move
    for (int i = 0; i <= 100; i = i + 5)
    {
        expander.setDutyCycle(ENABLE_A, i);
        delay(3000);
    }
}