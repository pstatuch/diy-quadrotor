
#include <Arduino.h>
#include "esc.h"
#include "state.h"
#include "gyro.h"
#include "receiver.h"

BMI160 imu(0x69, 6, 7);
IMUData imuData;

void setup() {
    setupStateLED();
    setDroneState(DroneState::DISCONNECTED);
    
    if (!imu.begin()) {
        setDroneState(DroneState::ERROR);
        while (true)
            delay(1000);
    }
    setDroneState(DroneState::DISCONNECTED);

}

void loop(){
}