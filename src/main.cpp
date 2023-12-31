#include <Arduino.h>
#include "temt6000.h"
#include "mq2.h"

temt *temt6000;
mq2 *_mq2 = new mq2();

void setup()
{
  Serial.begin(9600);
  EEPROM.begin(512);
  _mq2->checkCalibratedValue();
}

void loop()
{
  /************************** TEMT6000 Light Sensor *****************************/

  // temt6000->lightPercent();
  // delay(500);
  // temt6000->lightLux();
  // delay(500);

  /************************** MQ2 Gas Sensor *****************************/

  _mq2->readCalibratedValue();
  delay(500);
}
