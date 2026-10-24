#include <Arduino.h>
#include <ESP32Servo.h>
#include "esc.h"
#include "config.h"

const int PWM_CHANNEL = 0;
const int PWM_FREQUENCY = 50;
const int PWM_RESOLUTION = 14;

const uint32_t FRAME_LENGTH_US = 20000;
const uint32_t MIN_PULSE_US = 1000;
const uint32_t MAX_PULSE_US = 2000;

static constexpr uint8_t MOTOR_PINS[EscController::MOTOR_COUNT] = {
    ESC_FL_PIN, ESC_RL_PIN, ESC_FR_PIN, ESC_RR_PIN
};

void setEscPulse(uint32_t pulseUs) {
#ifdef BATTERY_2S
  uint32_t outputUs = FRAME_LENGTH_US - pulseUs;
#else
  uint32_t outputUs = pulseUs;
#endif

  const uint32_t maxDuty = (1UL << PWM_RESOLUTION) - 1;
  uint32_t duty = outputUs * maxDuty / FRAME_LENGTH_US;

  ledcWrite(PWM_CHANNEL, duty);
}

void EscController::begin() {
    initialized = true;

    for (uint8_t i = 0; i < MOTOR_COUNT; i++) {
        double actualFrequency = ledcSetup(
            PWM_CHANNELS[i],
            PWM_FREQUENCY,
            PWM_RESOLUTION
        );

        if (actualFrequency <= 0) {
            initialized = false;
            return;
        }

        ledcAttachPin(MOTOR_PINS[i], PWM_CHANNELS[i]);
        setMotorPulse(i, MIN_PULSE_US);
    }
}

void EscController::setMotorPulse(
    uint8_t motor,
    uint16_t pulseUs
) {
    if (!initialized || motor >= MOTOR_COUNT) {
        return;
    }

    pulseUs = constrain(
        pulseUs,
        MIN_PULSE_US,
        MAX_PULSE_US
    );

    uint32_t outputUs = pulseUs;

#ifdef BATTERY_2S
    outputUs = FRAME_LENGTH_US - pulseUs;
#endif

    const uint32_t maxDuty =
        (1UL << PWM_RESOLUTION) - 1;

    const uint32_t duty =
        outputUs * maxDuty / FRAME_LENGTH_US;

    ledcWrite(PWM_CHANNELS[motor], duty);
}

void EscController::setAllMotors(uint16_t pulseUs) {
    for (uint8_t i = 0; i < MOTOR_COUNT; i++) {
        setMotorPulse(i, pulseUs);
    }
}