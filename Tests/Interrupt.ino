#include "Expander.h"

Expander expander;

#define ENABLE_A 0
#define IN1 1
#define IN2 2

#define PIN_INTERRUPT 2

void setup()
{
    expander.begin();
    expander.setDutyCycle(ENABLE_A, 100); // Enable
    expander.setDutyCycle(IN1, 100);      // Cloclwise
    expander.setDutyCycle(IN2, 0);        // Counterclockwise

    pinMode(PIN_INTERRUPT, INPUT);
    if (digitalRead(PIN_INTERRUPT) == HIGH)
    {
        attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), count, FALLING);
    }
    else
    {
        attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), count, RISING);
    }
}

int counter = 0;
void count()
{
    counter++;
}

void loop()
{
    if (counter >= 20)
    {
        expander.setDutyCycle(ENABLE_A, 0);
    }
}