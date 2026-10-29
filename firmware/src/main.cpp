
#include <Arduino.h>
#include "esc.h"
#include "state.h"
#include "gyro.h"
#include "receiver.h"
#include "debug.h"

EscController esc;
uint16_t* chanels;

void setup() {
    DEBUG_BEGIN();
    DEBUG_PRINTLN("Initializing... (Status LED)");
    setupStateLED();
    DEBUG_PRINTLN("Status LED ready.");
    
    DEBUG_PRINTLN("Initializing... (ESCs)");
    esc.begin();
    DEBUG_PRINTLN("ESCs ready");

    DEBUG_PRINTLN("Initializing drone status");
    setDroneState(DroneState::DISCONNECTED);
    DEBUG_PRINTLN("Drone status: (Disconnected)");
    

    DEBUG_PRINTLN("Initializing connection with controller");
    initReceiver();
    setDroneState(DroneState::CONNECTED);
    DEBUG_PRINTLN("Controller connected");
    chanels =  updateChanels();
}

void loop(){
    
    
   updateChanels();
   
   float throttle = (chanels[2] - 170.0f) / (1785.0f-185.0f);
   Serial.print(throttle);
   Serial.print(" ");
   Serial.print(chanels[2]);
   Serial.println("");
   esc.setAllMotors(throttleToPwm(throttle));
   
}