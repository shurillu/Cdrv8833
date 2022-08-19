#ifndef DRV8833_H
#define DRV8833_H

#include <stdint.h>

// default values
#define PWM_FREQUENCY    5000 // 1 - 50000 Hz
#define PWM_BIT_RESOLUTION  8 // pwm bit resolution

// https://learn.adafruit.com/improve-brushed-dc-motor-performance/choosing-decay-mode-and-pwm-frequency
// DRV8833 PWM: min - 1Hz, max - 50KHz (provare 100-500Hz)
// PWM utilizzare le funzioni ledc 

// slow decay -> good torque, high power consumption
// fast decay -> poor torque, low power consumption
enum drv8833DecayMode {
	drv8833DecaySlow = 0,
	drv8833DecayFast = 1
};

class Cdrv8833 {
public:
	// default constructor. Default decay mode: SLOW
	Cdrv8833();

	// Specialized constructor. Default decay mode: SLOW
	// input:
	//   in1Pin       : DRV8833 AIN1/BIN1  
	//   in2Pin       : DRV8833 AIN2/BIN2
	//   channel      : ESP32 PWM channel (0..15) - ESP32 ledc functions
	//   swapDirection: swap motor rotation direction
	Cdrv8833(uint8_t in1Pin, uint8_t in2Pin, uint8_t channel, bool swapDirection = false);
	~Cdrv8833();

	// Initialize the DRV8833 object. Default decay mode: SLOW
	// input:
	//   in1Pin       : DRV8833 AIN1/BIN1  
	//   in2Pin       : DRV8833 AIN2/BIN2
	//   channel      : ESP32 PWM channel (0..15) - ESP32 ledc functions
	//   swapDirection: swap motor rotation direction
	// return:
	//   true if no error occurs.
	bool init(uint8_t in1Pin, uint8_t in2Pin, uint8_t channel, bool swapDirection = false);

	// Set motor rotation direction/speed
	// input:
	//   power: rotation power. -100..100
	//          Negative numbers mean reverse rotation; positive numbers mean forward direction.
	//          Zero stop the rotation
	// return:
	//   true if no error occurs.
	bool move(int8_t power); // use fast decay -> smooth movement

	// Stop the motor, using fast decay mode
	// return:
	//   true if no error occurs.
	bool stop();

	// Stop the motor, using slow decay mode
	// return:
	//   true if no error occurs.
	bool brake();

	// Set the decay mode. Default decay mode: SLOW
	// input:
	//   decayMode: new decay mode. Values are
	//              drv8833DecaySlow - good torque, high power consumption
	//              drv8833DecayFast - poor torque, low power consumption
	void setDecayMode(drv8833DecayMode decayMode);

	// Set the PWM frequency (for ESP32 ledc functions)
	// input:
	//   frequency: new frequency in Hertz. 1..50000Hz. 
	void setFrequency(uint32_t frequency);

	// Swap the motor rotation direction.
	// Useful for wrong cabling / driving two opposite motors (left wheel + right wheel motor of a vehicle)
	// input:
	//   swapDirection: true -> swap rotation direction 
	void swapDirection(bool swapDirection);

private:
	int8_t m_in1Pin;
	int8_t m_in2Pin;
	bool m_swapDirection;
	drv8833DecayMode m_decayMode;
	uint8_t m_channel;
	int8_t  m_power;
};

#endif
