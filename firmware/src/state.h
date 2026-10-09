#ifndef STATE_H
#define STATE_H

enum class DroneState {
    ERROR,
    DISCONNECTED,
    CONNECTED,
    ARMED,
    DATA_RECEIVED
};

void setupStateLED();
void setDroneState(DroneState state);

#endif