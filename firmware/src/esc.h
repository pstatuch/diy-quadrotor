
#pragma once

#include "config.h"
#include <Arduino.h>

const uint8_t ESC_FL = ESC_FL_PIN;
const uint8_t ESC_RL = ESC_RL_PIN;
const uint8_t ESC_FR = ESC_FR_PIN;
const uint8_t ESC_RR = ESC_RR_PIN;

class EscController {
public:
    static constexpr uint8_t MOTOR_COUNT = 4;

    void begin();

    void setMotorPulse(uint8_t motor, uint16_t pulseUs);

    // Ustawia jednakową przepustnicę dla wszystkich silników
    void setAllMotors(uint16_t pulseUs);

private:
    inline static constexpr uint8_t PWM_CHANNELS[MOTOR_COUNT] = {
        ESC_FL, ESC_RL, ESC_FR, ESC_RR
    };

    static constexpr uint16_t MIN_PULSE_US = 1000;
    static constexpr uint16_t MAX_PULSE_US = 2000;

    static constexpr uint32_t FRAME_LENGTH_US = 20000;
    static constexpr uint32_t PWM_FREQUENCY = 50;
    static constexpr uint8_t PWM_RESOLUTION = 14;

    bool initialized = false;
};
