#ifndef _CompositeXpto_h_
#define _CompositeXpto_h_

#include <Arduino.h>

#include "Xpto.h"

class CompositeXpto
{
private:
    Xpto *x1;
    Xpto *x2;
    static CompositeXpto *isrHandler;

public:
    CompositeXpto(Xpto *_x1, Xpto *_x2);

    /*
     * https://esp32.com/viewtopic.php?t=4978
     */
    IRAM_ATTR static void handleX1();
    IRAM_ATTR static void handleX2();
};

#endif // _CompositeXpto_h_
