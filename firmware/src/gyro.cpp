
#include "gyro.h"

BMI160::BMI160(uint8_t address, int sdaPin, int sclPin)
    : address(address), sdaPin(sdaPin), sclPin(sclPin) {
}

uint8_t BMI160::readRegister(uint8_t reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);

    if (Wire.endTransmission(false) != 0)
        return 0xFF;

    if (Wire.requestFrom(address, (uint8_t)1) != 1)
        return 0xFF;

    return Wire.read();
}

bool BMI160::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(value);

    return Wire.endTransmission() == 0;
}

bool BMI160::readRegisters(
    uint8_t reg, uint8_t *data, size_t len) {

    Wire.beginTransmission(address);
    Wire.write(reg);

    if (Wire.endTransmission(false) != 0)
        return false;

    if (Wire.requestFrom(address, (uint8_t)len) != len)
        return false;

    for (size_t i = 0; i < len; i++)
        data[i] = Wire.read();

    return true;
}

int16_t BMI160::toInt16(uint8_t low, uint8_t high) {
    return (int16_t)(((uint16_t)high << 8) | low);
}

bool BMI160::begin() {
    Wire.begin(sdaPin, sclPin);
    Wire.setClock(100000);

    if (readRegister(0x00) != 0xD1)
        return false;

    // Akcelerometr: tryb normalny
    if (!writeRegister(0x7E, 0x11))
        return false;

    delay(50);

    // Zyroskop: tryb normalny
    if (!writeRegister(0x7E, 0x15))
        return false;

    delay(100);

    return true;
}

bool BMI160::read(IMUData &data) {
    uint8_t buffer[12];

    if (!readRegisters(0x0C, buffer, sizeof(buffer)))
        return false;

    data.gyroXRaw = toInt16(buffer[0], buffer[1]);
    data.gyroYRaw = toInt16(buffer[2], buffer[3]);
    data.gyroZRaw = toInt16(buffer[4], buffer[5]);

    data.accelXRaw = toInt16(buffer[6], buffer[7]);
    data.accelYRaw = toInt16(buffer[8], buffer[9]);
    data.accelZRaw = toInt16(buffer[10], buffer[11]);

    // Domyslne zakresy: gyro +/-2000 stopni/s,
    // accel +/-2g
    data.gyroX = data.gyroXRaw / 16.4f;
    data.gyroY = data.gyroYRaw / 16.4f;
    data.gyroZ = data.gyroZRaw / 16.4f;

    data.accelX = data.accelXRaw / 16384.0f;
    data.accelY = data.accelYRaw / 16384.0f;
    data.accelZ = data.accelZRaw / 16384.0f;

    return true;
}
