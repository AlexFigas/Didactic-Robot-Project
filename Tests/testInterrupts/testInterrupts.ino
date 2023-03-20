#include <Arduino.h>

#include "Xpto.h"
#include "CompositeXpto.h"

const uint8_t intPin1 = 18;
const uint8_t intPin2 = 19;

Xpto x1(intPin1);
Xpto x2(intPin2);

CompositeXpto composite(&x1, &x2);

int lastX1, lastX2;

void setup()
{
    Serial.begin(115200);

    while (!Serial)
        ;

    lastX1 = lastX2 = 0;

    Serial.println("Serial ready.");
}

void show(const char *name, int &lastX, Xpto *x)
{
    int currentX = x->getCounter();

    if (currentX != lastX)
    {
        lastX = currentX;
        Serial.print(name);
        Serial.print(" = ");
        Serial.println(currentX);
    }
}

void loop()
{
    show("X1", lastX1, &x1);
    show("X2", lastX2, &x2);
}
