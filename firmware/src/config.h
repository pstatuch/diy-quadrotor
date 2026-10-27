#include "debug.h"

#pragma once

// if ENABLE_DEBUGGING defined Serial will be activated  
// comment out in final code
#define ENABLE_DEBUGGING

// choose one battery / ESC type:
#define BATTERY_2S
// #define BATTERY_1S

#if defined(BATTERY_1S) && defined(BATTERY_2S)
  #error "Choose only one battery type"
#endif

#if !defined(BATTERY_1S) && !defined(BATTERY_2S)
  #error "No battery battery type selected"
#endif

// bind ESC pins
#define ESC_FL_PIN 0
#define ESC_RL_PIN 1
#define ESC_FR_PIN 2
#define ESC_RR_PIN 3

// bind Gyro I2C pins
#define GYRO_I2C_SDA 6
#define GYRO_I2C_SCL 7

// bind RADIO receiver UART pins
#define RADIO_UART_RX_PIN 20
#define RADIO_UART_TX_PIN 21
