#include "CompositeXpto.h"

CompositeXpto *CompositeXpto::isrHandler;

CompositeXpto::CompositeXpto(Xpto *_x1, Xpto *_x2)
{
    this->x1 = _x1;
    this->x2 = _x2;

    CompositeXpto::isrHandler = this;

    // Ou em alternativa 2 de 3
    attachInterrupt(
        digitalPinToInterrupt(this->x1->getPin()),
        CompositeXpto::handleX1,
        RISING);
    attachInterrupt(
        digitalPinToInterrupt(this->x2->getPin()),
        CompositeXpto::handleX2,
        RISING);

    // Ou em alternativa 3 de 3
    attachInterrupt(
        digitalPinToInterrupt(this->x1->getPin()),
        []()
        {
            CompositeXpto::isrHandler->x1->incrementCounter();
        },
        RISING);
    attachInterrupt(
        digitalPinToInterrupt(this->x2->getPin()),
        []()
        {
            CompositeXpto::isrHandler->x2->incrementCounter();
        },
        RISING);
}

void CompositeXpto::handleX1()
{
    CompositeXpto::isrHandler->x1->incrementCounter();
}

void CompositeXpto::handleX2()
{
    CompositeXpto::isrHandler->x2->incrementCounter();
}
