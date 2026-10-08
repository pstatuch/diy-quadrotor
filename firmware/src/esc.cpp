#include <Arduino.h>
#include <ESP32Servo.h>
#include "esc.h"

#define ESC_PIN 4

Servo esc;

void escInit() {
    esc.setPeriodHertz(50);
    esc.attach(ESC_PIN, 1000, 2000);

    esc.writeMicroseconds(1000);

    delay(3000);
}

void escSetThrottle(int microseconds) {
    esc.writeMicroseconds(microseconds);
}

void escStop() {
    esc.writeMicroseconds(1000);
}