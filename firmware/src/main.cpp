#include <Arduino.h>
#include "esc.h"
#include "state.h"


DroneState currentState = DroneState::DISCONNECTED;


void setup() {
    setupStateLED();
    currentState = DroneState::DISCONNECTED;
    setDroneState(currentState);
}


void loop() {

    // change state check
    delay(5000);
    currentState = currentState != DroneState::ARMED ? DroneState::ARMED : DroneState::CONNECTED;
    setDroneState(currentState);
    
    
}

