#include "Expander.h"

Expander expander();

void setup()
{
    expander.begin();
    expander.setDutyCycle(15, 100);
}

void loop()
{
    
}