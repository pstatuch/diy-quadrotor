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
 | Red | ERROR | N/A | N/A |
 | Yellow | Disconnected | no | no |
 | Blue | Connected | YES | no |
 | Green | Armed |  YES | YES |
 | White | Data received | N/A | N/A |

 states ERROR and DATA_RECEIVED represent events, not long running state and can happen at any time : 
 - problem / success while reading gyro data
 - problem / success while reading controller commands
 - unexpected exception
 - other
 
# Module integration
## BMI160 gyro

Protocol IC2

connection
```
 ESP32         BMI160
-------        -------
| GND | -----> | GND |
| 3v3 | -----> | 3V3 | 
|  6  | -----> | SCL |
|  7  | -----> | SDA | 
```

clock speed: 100 kHz