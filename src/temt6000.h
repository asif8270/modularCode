#ifndef temt6000_H
#define temt6000_H

#include <Arduino.h>
#define sigPin (GPIO_NUM_13);

class temt
{
public:
    void lightPercent();
    void lightLux();
};

#endif