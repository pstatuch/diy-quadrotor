#pragma once
#include "config.h"

#ifdef ENABLE_DEBUGGING

    #define DEBUG_BEGIN() Serial.begin(115200)

    #define DEBUG_PRINT(...) \
        do { Serial.printf(__VA_ARGS__); } while (0)

    #define DEBUG_PRINTLN(...) \
        do { Serial.println(__VA_ARGS__); } while (0)

#else

    #define DEBUG_BEGIN() do {} while (0)

    #define DEBUG_PRINT(...) do {} while (0)

    #define DEBUG_PRINTLN(...) do {} while (0)

#endif