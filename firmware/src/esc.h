
#pragma once

#include "config.h"
#include <Arduino.h>

const uint8_t ESC_FL = 0;
const uint8_t ESC_RL = 1;
const uint8_t ESC_FR = 2;
const uint8_t ESC_RR = 3;

class EscController {
public:
    static constexpr uint8_t MOTOR_COUNT = 4;

    void begin();

    // motor: indeks od 0 do 3
    // pulseUs: długość impulsu sterującego w mikrosekundach
    void setMotorPulse(uint8_t motor, uint16_t pulseUs);

    // Ustawia jednakową przepustnicę dla wszystkich silników
    void setAllMotors(uint16_t pulseUs);

private:
    static constexpr uint8_t PWM_CHANNELS[MOTOR_COUNT] = {
        ESC_FL, ESC_RL, ESC_FR, ESC_RR
    };

    static constexpr uint16_t MIN_PULSE_US = 1000;
    static constexpr uint16_t MAX_PULSE_US = 2000;

    static constexpr uint32_t FRAME_LENGTH_US = 20000;
    static constexpr uint32_t PWM_FREQUENCY = 50;
    static constexpr uint8_t PWM_RESOLUTION = 14;

    bool initialized = false;
};
