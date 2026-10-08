# diy-quadrotor

## Drone state:
Firmware uses ESP32 C2 mini onboard diode to indicate current state, check state table below.
 

 |Diode color| State | Controller paired | ESC armed | 
 | --- | --- | --| -- |
 | Yellow | Disconnected | no | no |
 | Blue | CONNECTED | YES | no |
 | Green | Armed |  YES | YES |
 
    