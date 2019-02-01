# Phase Goal
Creating an API for the higher level applications. Any application for the product would be built through the API, thus it'll act as middleware for all purposes.

## Main API Goals
- [ ] **RAW sensor data output**: This is basically the output of all sensors in _raw_ format.
- [ ] **Frames**: This outputs the frames of all the joints
    - In the final product, we'll have four 3 joint fingers (longer fingers) and a single two joint finger (the thumb), so completely 14 joints + one frame for IMU (base frame for everything).
    - Frame tracking through IMU must also be implemented
- [ ] **Pulse sensor**: The BPM readings from the pulse sensor (waveform is in _RAW output form_). This will be used for anomaly detection in the heartbeat pattern.

## Distribution of items
Every member has sensor items and a board for learning development on TI Code Composer Studio or Energia platform.

| **Items** | **User name** | **Board** |
| ----- | ---- | ---- |
| IMU | @supaboi21 | `MSP430FR2355` development board |
| Flex Sensor | @TheProjectsGuy | `CC3220` launchpad |
| Pulse Sensor | @bharath0404 | `CC2640R2` launchpad |

### Individual end results needed
#### IMU
- [ ] Algorithm
- [ ] Code, with documentation, for interfacing TI board with the IMU sensor

#### Flex Sensor
- [ ] Algorithm for mapping
- [ ] Code, with documentation for interfacing TI board with the flex sensor circuitry

#### Pulse Sensor
- [ ] Algorithm for pulse measurement and anomaly detection
- [ ] Code, with documentation for interfacing TI board with the pulse sensor