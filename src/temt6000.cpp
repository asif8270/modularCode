#include <Arduino.h>
#include "temt6000.h"

// calculating light coming from source

// Light in percentage
void temt::lightPercent()
{
    float voltage;
    float percent;
    pinMode(GPIO_NUM_13, INPUT);         // Defining sigPin as Input
    voltage = (analogRead(13) / 4095.0); // reading sensor's value (signal)
    percent = voltage * 100.0;           // calculating light in percentage
    Serial.print("Light ");
    Serial.print(percent);
    Serial.print(" %\n");
}

// light in lux
void temt::lightLux()
{
    pinMode(GPIO_NUM_13, INPUT); // Defining sigPin as Input

    /* First formula to calculate light in lux*/

    float volts = (analogRead(GPIO_NUM_13) * 3.30) / 4095.0; // converting analog values b/w 1-5 volts
    float mAmps = (volts / 10000.0) * 1000000.0;             //  calculating mAmps I = (V/R)*1000000
    float lux = mAmps * 2.0;                                 // calculating lux

    /* Second formula to calculate light in lux*/
    /* Uncomment following two lines for second formula*/

    // float reading = (analogRead(GPIO_NUM_13) / 1023.0);
    // float sq_ration = pow(reading, 2.0);
    Serial.print(lux);
    Serial.print(" lux\n");
}
