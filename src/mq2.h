#ifndef mq2_H
#define mq2_H

#include <Arduino.h>
#include <EEPROM.h>

#define MQ_PIN (GPIO_NUM_34)       // define which analog input channel you are going to use
#define RL_VALUE (10)              // define the load resistance on the board, in kilo ohms
#define RO_CLEAN_AIR_FACTOR (9.83) // RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                   // which is derived from the chart in datasheet

/***********************Software Related Macros************************************/
#define CALIBARAION_SAMPLE_TIMES (50)     // define how many samples you are going to take in the calibration phase
#define CALIBRATION_SAMPLE_INTERVAL (500) // define the time interal(in milisecond) between each samples in the
                                          // cablibration phase
#define READ_SAMPLE_INTERVAL (50)         // define how many samples you are going to take in normal operation
#define READ_SAMPLE_TIMES (5)             // define the time interal(in milisecond) between each samples in
                                          // normal operation

/**********************Application Related Macros**********************************/
#define GAS_LPG (0)
#define GAS_CO (1)
#define GAS_SMOKE (2)

#define CALIBRATION_ADDRESS 8      // EEPROM address for storing the calibrated value
#define CALIBRATION_FLAG_ADDRESS 9 // EEPROM address for storing the calibration flag

class mq2
{
private:
    float LPGCurve[3] = {2.3, 0.21, -0.47};
    float COCurve[3] = {2.3, 0.72, -0.34};
    float SmokeCurve[3] = {2.3, 0.53, -0.44};
    float Ro = 10; // Ro is initialized to 10 kilo ohms
public:
    float MQCalibration(int mq_pin);
    float MQRead(int mq_pin);
    float MQGetGasPercentage(float rs_ro_ratio, int gas_id);
    float MQGetPercentage(float rs_ro_ratio, float *pcurve);
    float MQResistanceCalculation(int raw_adc);
    void calibrateMQ2();
    void checkCalibratedValue();
    void readCalibratedValue();
    // mq2();
    // ~mq2();
};
// mq2::mq2()
// {
//     EEPROM.begin(512);
// }
// mq2::~mq2()
// {
// }
#endif