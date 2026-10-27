#include <Adafruit_NeoPixel.h>
#include "state.h"
#include "config.h"

#define NUM_LEDS 1

#if defined( STATUS_LED_PIN ) && defined(STATUS_LED_RGB) 

    Adafruit_NeoPixel led(NUM_LEDS, STATUS_LED_PIN, NEO_GRB + NEO_KHZ800);
    void setupStateLED() {
    led.begin();
    led.clear();
    led.show();
    led.setBrightness(125);

    }

    void setDroneState(DroneState state) {
        switch (state) {
            case DroneState::DISCONNECTED:
                led.setPixelColor(0, led.Color(255, 255, 0));
                break;

            case DroneState::CONNECTED:
                led.setPixelColor(0, led.Color(0, 0, 255));
                break;

            case DroneState::ARMED:
                led.setPixelColor(0, led.Color(0, 255, 0));
                break;
            case DroneState::ERROR:
                led.setPixelColor(0, led.Color(255, 0, 0));
                break;
            case DroneState::DATA_RECEIVED:
                led.setPixelColor(0, led.Color(255, 255, 255));
                break;
        }

        led.show();
    }
#elif defined( STATUS_LED_PIN )
    void setupStateLED() {
        pinMode(STATUS_LED_PIN, OUTPUT);
    }

    void setDroneState(DroneState state) {
        switch (state) {
            case DroneState::DISCONNECTED:
            case DroneState::ERROR:
                digitalWrite(STATUS_LED_PIN, LOW);
                break;
            case DroneState::CONNECTED:
            case DroneState::ARMED:
                digitalWrite(STATUS_LED_PIN, HIGH);
                break;
            case DroneState::DATA_RECEIVED:
                break;
            default:
                break;
        }
    }

#endif




