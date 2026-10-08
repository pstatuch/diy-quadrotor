#include <Adafruit_NeoPixel.h>
#include "state.h"

#define LED_PIN 10
#define NUM_LEDS 1

Adafruit_NeoPixel led(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


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
    }

    led.show();
  }

