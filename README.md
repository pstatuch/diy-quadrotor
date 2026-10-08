# diy-quadrotor

## Parts list:
This drone is desing to be budget friendly, all parts can be bought on `Aliexpress`. 

- EST32 C3 mini
- `Aliexpres` 1s-2s mini ESC
- 2s li-po battery
- 2s 1503 brushless engines
- DC Buck Converter 5-30V to 5V
- BMI160 6-Axis Rate Gyro / Accelerometer sensor
- 3d-printed frame
- (Optional) ELRS receiver and controller


## Drone state:
Firmware uses ESP32 C3 mini onboard diode to indicate current state, check state table below.
 

 |Diode color| State | Controller paired | ESC armed | 
 | --- | --- | --| -- |
 | Yellow | Disconnected | no | no |
 | Blue | Connected | YES | no |
 | Green | Armed |  YES | YES |
 
    