/*
    Name:       drv8833Tester.ino
    Created:	16/08/2022 10:06:02
    Author:     Stefano Ledda
    Email:      shurillu@tiscalinet.it
    GitHub:     https://github.com/shurillu/Cdrv8833
    Note:       Simple sketch to test the DRV8833 H-Bridge
                - connect the GPIO 12 to the xIN1 of the DRV8833 module
                - connect the GPIO 13 to the xIN2 of the DRV8833 module
                - connect the positive pole of the motor to the xOUT1 of the DRV8833 module
                - connect the negative pole of the motor to the xOUT2 of the DRV8833 module
                - power the DRV8833 module (if the motor is small, 5V and <500mA, you can power
                  the module pulling the 5V and GND from the ESP32 board)
                - load the sketch
                - use the serial console to send commands
*/

#include "Cdrv8833.h"

#define IN1_PIN    12 // in1 pin from one of the two DRV8833 H-bridge
#define IN2_PIN    13 // in2 pin from one of the two DRV8833 H-bridge
#define CHANNEL     0 // there are 16 unique PWM channels (0..15)
#define SWAP    false // swap motor rotation direction

Cdrv8833 myMotor; // default constructor

// you can initialize the object directly with the specialized constructor:
// Cdrv8833 myMotor2(IN1_PIN, IN2_PIN, CHANNEL, SWAP);

void setup()
{
    Serial.begin(115200);
    Serial.println("\n");
    Serial.println("DRV8833 tester");
    Serial.println("--------------");
    Serial.printf("IN1 pin: %u\nIN2 pin: %u\n\n", IN1_PIN, IN2_PIN);

    Serial.println("SWAP    - swap motor rotation direction.");
    Serial.println("NOSWAP  - restore motor rotation direction.");
    Serial.println("SLOW    - decay mode SLOW - good torque, high power consumption.");
    Serial.println("FAST    - decay mode FAST - poor torque, low power consumption.");
    Serial.println("MOVEXXX - start rotation (XXX = -100..100).");
    Serial.println("STOP    - stop the motor.");

    // initialize the object. Not needed if the initialization is done with the specialized constructor
    myMotor.init(IN1_PIN, IN2_PIN, CHANNEL, SWAP);
}

void loop()
{
    String command;
    if (Serial.available()) { // check Serial for new command
        command = Serial.readString(); // read the new command from Serial
        command.toLowerCase(); // convert it to lowercase

        if (command.equals("swap")) {
            myMotor.swapDirection(true); // swap rotation direction
            Serial.println("--> swapped rotation direction.");
        }
        else if (command.equals("noswap")) {
            myMotor.swapDirection(false); // default rotation direction
            Serial.println("--> default rotation direction.");
        }
        else if (command.equals("slow")) {
            myMotor.setDecayMode(drv8833DecaySlow); // decay mode SLOW
            Serial.println("--> Decay mode SLOW - good torque.");
        }
        else if (command.equals("fast")) {
            myMotor.setDecayMode(drv8833DecayFast); // decay mode FAST
            Serial.println("--> Decay mode FAST - poor torque.");
        }
        else if (command.equals("stop")) {
            myMotor.stop(); // stop moto rotation
            Serial.println("--> Motor stopped.");
        }
        else if (command.startsWith("move")) {
            command.replace("move", ""); // remove the word "move"
            command.replace(" ", "");    // remove spaces (if present)
            myMotor.move(command.toInt()); // start rotation at desired speed
            Serial.printf("--> Motor rotation speed: %ld.\n", command.toInt());
        }
    }
}
