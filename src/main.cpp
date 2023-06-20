#include <Arduino.h>
#include "temt6000.h"
#include "mq2.h"

temt *temt6000;
mq2 *_mq2 = new mq2();

void setup()
{
  Serial.begin(9600);
  _mq2->checkCalibratedValue();
  // _mq2 = new mq2();
  // float rs = _mq2->MQRead(MQ_PIN);
}

void loop()
{
  // temt6000->lightPercent();
  // delay(500);
  // temt6000->lightLux();
  // delay(500);
  /************************** MQ2 Gas Sensor *****************************/
  _mq2->readCalibratedValue();
  delay(500);
}
