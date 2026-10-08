#ifndef STATE_H
#define STATE_H

enum class DroneState {
    DISCONNECTED,
    CONNECTED,
    ARMED
};

void setupStateLED();
void setDroneState(DroneState state);

#endif