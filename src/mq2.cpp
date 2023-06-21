#include <Arduino.h>
#include "mq2.h"
#include <EEPROM.h>

// Check if calibration has been performeds
void mq2::checkCalibratedValue()
{
    // Read the calibration flag from EEPROM

    if (EEPROM.read(9) != 1)
    {
        // Calibration has not been performed or manual recalibration requested
        calibrateMQ2();
    }
}

void mq2::readCalibratedValue()
{
    Serial.print("\nEEPROM Ro: ");
    Serial.print(EEPROM.read(8));
    Serial.print(" kOhm");
    Serial.print("\n");
    Serial.print("LPG:");
    Serial.print(MQGetGasPercentage(MQRead(MQ_PIN) / EEPROM.read(8), GAS_LPG));
    Serial.print("ppm");
    Serial.print("    ");
    Serial.print("CO:");
    Serial.print(MQGetGasPercentage(MQRead(MQ_PIN) / EEPROM.read(8), GAS_CO));
    Serial.print("ppm");
    Serial.print("    ");
    Serial.print("SMOKE:");
    Serial.print(MQGetGasPercentage(MQRead(MQ_PIN) / EEPROM.read(8), GAS_SMOKE));
    Serial.print("ppm");
    Serial.print("\n");
}

void mq2::calibrateMQ2()
{
    pinMode(34, INPUT);
    // Calibrating the MQ2 sensor
    Serial.print("\nCalibrating...");
    float calibratedRo = MQCalibration(MQ_PIN); // Storing the calibrated Ro
    Serial.print("Calibration is done...\n");
    Serial.print("Calibirated Ro = ");
    Serial.print(calibratedRo);
    Serial.print("kohm");
    Serial.print("\n");
    EEPROM.write(8, calibratedRo); // Saving the calibrated Ro to EEPROM
    EEPROM.write(9, 1);            // Set the calibration flag to indicate that calibration has been performed
    EEPROM.commit();               // Commit changes to EEPROM
}

float mq2::MQResistanceCalculation(int raw_adc)
{
    return (((float)RL_VALUE * (4096 - raw_adc) / raw_adc));
}

float mq2::MQCalibration(int mq_pin)
{
    int i;
    float val = 0;
    for (i = 0; i < CALIBARAION_SAMPLE_TIMES; i++)
    {
        // take multiple samples
        val += MQResistanceCalculation(analogRead(mq_pin));
        delay(CALIBRATION_SAMPLE_INTERVAL);
    }
    val = val / CALIBARAION_SAMPLE_TIMES; // calculate the average value

    val = val / RO_CLEAN_AIR_FACTOR; // divided by RO_CLEAN_AIR_FACTOR yields the Ro
                                     // according to the chart in the datasheet
    return val;
}

float mq2::MQRead(int mq_pin)
{
    int i;
    float rs = 0;

    for (i = 0; i < READ_SAMPLE_TIMES; i++)
    {
        rs += MQResistanceCalculation(analogRead(mq_pin));
        delay(READ_SAMPLE_INTERVAL);
    }

    rs = rs / READ_SAMPLE_TIMES;

    return rs;
}

float mq2::MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
    if (gas_id == GAS_LPG)
    {
        return MQGetPercentage(rs_ro_ratio, LPGCurve);
    }
    else if (gas_id == GAS_CO)
    {
        return MQGetPercentage(rs_ro_ratio, COCurve);
    }
    else if (gas_id == GAS_SMOKE)
    {
        return MQGetPercentage(rs_ro_ratio, SmokeCurve);
    }

    return 0;
}

float mq2::MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
    return (pow(10, (((log(rs_ro_ratio) - pcurve[1]) / pcurve[2]) + pcurve[0])));
}