#include "Xpto.h"
#include "FunctionalInterrupt.h"

Xpto::Xpto(int _pin) : counter(0), pin(_pin)
{
    pinMode(this->pin, INPUT_PULLUP);

    // Ou em alternativa 1 de 3
    attachInterrupt(
        digitalPinToInterrupt(this->pin),
        std::bind(&Xpto::incrementCounter, this),
        RISING);
}

void Xpto::incrementCounter()
{
    ++this->counter;
}

int Xpto::getCounter()
{
    return this->counter;
}

void Xpto::resetCounter()
{
    this->counter = 0;
}

int Xpto::getPin()
{
    return this->pin;
}
