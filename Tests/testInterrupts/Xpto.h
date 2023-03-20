#ifndef _Xpto_h_
#define _Xpto_h_

#include <Arduino.h>

class Xpto
{
private:
    /*
     * Volatile also causes the compiler to generate code that always reads the
     * variable from RAM and does not "cache" the last read value in a register.
     *
     * Volatile should ALWAYS be used on any variable that can be modified by an
     * interrupt, or any external source.
     */
    volatile int counter;
    int pin;

public:
    Xpto(int _pin);

    /*
     * https://esp32.com/viewtopic.php?t=4978
     */
    IRAM_ATTR void incrementCounter();
    int getCounter();
    void resetCounter();

    int getPin();
};

#endif // _Xpto_h_
