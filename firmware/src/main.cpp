
#include <Arduino.h>
#include "esc.h"
#include "state.h"
#include "gyro.h"
#include "receiver.h"
#include "debug.h"


EscController esc;
void setup() {
    DEBUG_BEGIN();
    DEBUG_PRINTLN("Initializing... (Status LED)");
    setupStateLED();
    DEBUG_PRINTLN("Status LED ready.");
    
    DEBUG_PRINTLN("Initializing... (ESCs)");
    esc.begin();
    DEBUG_PRINTLN("ESCs ready");

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

    esc.setAllMotors(1000);
    delay(1000);
    esc.setAllMotors(1500);
    delay(3000);
    esc.setAllMotors( 1000);


}