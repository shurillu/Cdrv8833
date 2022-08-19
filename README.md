# Cdrv8833

<img src="https://github.com/shurillu/Cdrv8833/blob/f3dccc3f0448b2a2071de1e72d5ad1d12b7a835d/images/DRV8833.jpg" alt="DRV8833 module" width="180"/>

### Introduction
Cdrv883 is a wrapper class for using modules based on DRV8833 H-bridge from Texas Instruments.

### News
+ First public version released.

### Simple usage
See the drv8833Tester example provided in the [examples folder](https://github.com/shurillu/Cdrv8833/tree/main/examples/drv8833Tester).

### Changelog
+ 1.0.0 Initial version.

<hr>

### Reference

#### `Cdrv8833()`
Default constructor. The object is NOT initialized: the `init` member function must be called. Decay mode is set to SLOW.
<br><br>

#### `Cdrv8833(uint8_t in1Pin, uint8_t in2Pin, uint8_t channel, bool swapDirection = false)`
Specialized constructor. Decay mode is set to SLOW.

input:
+ `in1Pin`: DRV8833 AIN1/BIN1
+ `in2Pin`: DRV8833 AIN2/BIN2
+ `channel`: ESP32 PWM channel (0..15) - ESP32 ledc functions
+ `swapDirection`: swap motor rotation direction

There are 16 independent channels for PWM modulation inside the ESP32 SOC. Every motor need to have its own channel in order to work independently each other.

Swapping the motor rotation direction is useful (for example):
+ wrong cabling
+ using two motors to drive a two wheels vehicle (left wheel, right wheel). 
<br><br>

#### `bool init(uint8_t in1Pin, uint8_t in2Pin, uint8_t channel, bool swapDirection = false)`
Initialize the object. Decay mode is set to SLOW.

input:
+ `in1Pin`: DRV8833 AIN1/BIN1
+ `in2Pin`: DRV8833 AIN2/BIN2
+ `channel`: ESP32 PWM channel (0..15) - ESP32 ledc functions
+ `swapDirection`: swap motor rotation direction

Return `true` if no error occurs.

There are 16 independent channels for PWM modulation inside the ESP32 SOC. Every motor need to have its own channel in order to work independently each other.

Swapping the motor rotation direction is useful (for example):
+ wrong cabling
+ using two motors to drive a two wheels vehicle (left wheel, right wheel). 
<br><br>

#### `bool move(int8_t power)`
Set motor rotation direction/speed.

input:
+ `power`: rotation power. -100..100

Return `true` if no error occurs.

The `power` parameter set the rotation speed and the direction. Negative values means reverse rotation direction. Value span to -100 (full speed reverse direction) to 100 (full speed forward direction).

Zero stop the motor rotation.
<br><br>

#### `bool stop()`
Stop the motor, using fast decay mode.

Return `true` if no error occurs.
<br><br>

#### `bool brake()`
Stop the motor, using slow decay mode.

Return `true` if no error occurs.
<br><br>

#### `void setDecayMode(drv8833DecayMode decayMode)`
Set the decay mode. Default decay mode is set to SLOW.

input:
+ `decayMode`: new decay mode. Values are
  + `drv8833DecaySlow` good torque, but high power consumption
  + `drv8833DecayFast` poor torque, but low power consumption
<br><br>

#### `void setFrequency(uint32_t frequency)`
Set the frequency used for the PWM modulation(for ESP32 ledc functions). Default value is 5000Hz. Allowed values are 1Hz..50000Hz.

input:
+ `frequency`: new frequency in Hertz. 1..50000Hz
<br><br>

#### `void swapDirection(bool swapDirection)`
Swap the motor rotation direction.
Useful for wrong cabling / driving two opposite motors (left wheel and right wheel of a vehicle)

input:
+ `swapDirection`: swap/unswap the motor rotation direction 
  + `true`: swap rotation direction 
  + `false`: default rotation direction


