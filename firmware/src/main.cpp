
#include <Arduino.h>
#include "esc.h"
#include "state.h"
#include "gyro.h"
#include "receiver.h"
#include "debug.h"


void setup() {
    DEBUG_BEGIN();
    setupStateLED();
    

    DEBUG_PRINT("Initializing drone status");
    setDroneState(DroneState::DISCONNECTED);
    delay(2000);
    
}

void loop(){
    setDroneState(DroneState::CONNECTED);
    DEBUG_PRINTLN("Switching state...(Connected)");

    delay(1000);
    
    setDroneState(DroneState::ARMED);
    DEBUG_PRINTLN("Switching state...(Armed)");
    delay(1000);

}