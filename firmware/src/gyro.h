#pragma once

#include <Arduino.h>
#include <Wire.h>

struct IMUData {
    // Surowe odczyty z czujnikow
    int16_t gyroXRaw = 0;
    int16_t gyroYRaw = 0;
    int16_t gyroZRaw = 0;

    int16_t accelXRaw = 0;
    int16_t accelYRaw = 0;
    int16_t accelZRaw = 0;

    // Wartosci przeliczone na jednostki fizyczne
    float gyroX = 0.0f;  // stopnie/s
    float gyroY = 0.0f;
    float gyroZ = 0.0f;

    float accelX = 0.0f; // g
    float accelY = 0.0f;
    float accelZ = 0.0f;
};

class BMI160 {
public:
    BMI160(uint8_t address = 0x69,
           int sdaPin = 6,
           int sclPin = 7);

    bool begin();
    bool read(IMUData &data);

private:
    uint8_t address;
    int sdaPin;
    int sclPin;

    uint8_t readRegister(uint8_t reg);
    bool writeRegister(uint8_t reg, uint8_t value);
    bool readRegisters(uint8_t reg,
                       uint8_t *data,
                       size_t len);

    static int16_t toInt16(uint8_t low, uint8_t high);
};