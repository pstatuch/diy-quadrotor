#pragma once

// choose one battery / ESC type:
#define BATTERY_2S
// #define BATTERY_1S

#if defined(BATTERY_1S) && defined(BATTERY_2S)
  #error "Choose only one battery type"
#endif

#if !defined(BATTERY_1S) && !defined(BATTERY_2S)
  #error "No battery battery type selected"
#endif

// bind ESC to pin

const uint8_t ESC_FL_PIN = 4;
const uint8_t ESC_RL_PIN = 5;
const uint8_t ESC_FR_PIN = 6;
const uint8_t ESC_RR_PIN = 7;

