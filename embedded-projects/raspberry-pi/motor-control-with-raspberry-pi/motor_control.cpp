/*
Motor Control with Raspberry Pi:

Description: Control a motor (e.g., DC motor or servo motor) using Raspberry Pi GPIO pins and C/C++.
Example: Write a program to control the speed and direction of a DC motor connected to Raspberry Pi GPIO pins.
In this example:

    We initialize the wiringPi library and define the GPIO pins connected to the motor driver (PWM pin for speed control and two direction pins).
    The initMotorPins function configures the GPIO pins as outputs.
    The controlMotor function sets the motor direction and speed by adjusting the PWM duty cycle on the PWM pin and setting the direction pins accordingly.
    In the main function, we continuously control the motor's speed and direction in a loop, alternating between different speeds and directions.

Make sure to connect the motor driver to the appropriate GPIO pins on the Raspberry Pi and provide an external power source for the motor. Additionally, adjust the GPIO pin numbers in the code according to your wiring configuration.

To test the provided code on a Raspberry Pi, follow these steps:

    Setup Raspberry Pi:
        Make sure your Raspberry Pi is set up with an operating system (such as Raspbian or Raspberry Pi OS).
        Ensure that the WiringPi library is installed on your Raspberry Pi. If not, you can install it using the following commands:

        sql

    sudo apt-get update
    sudo apt-get install wiringpi

Connect the Motor:

    Connect the DC motor to the motor driver (e.g., L298N).
    Connect the motor driver to the Raspberry Pi GPIO pins:
        Connect the PWM pin to GPIO pin 18 (or any PWM-capable pin).
        Connect the direction pins (DIR_PIN1 and DIR_PIN2) to GPIO pins 17 and 27, respectively.

Compile the Code:

    Copy the provided C++ code into a file on your Raspberry Pi (e.g., motor_control.cpp).
    Compile the code using the following command:

    g++ -o motor_control motor_control.cpp -lwiringPi

Run the Program:

    Run the compiled program with root privileges (as accessing GPIO pins requires root permissions):

    bash

        sudo ./motor_control

    Observe Motor Behavior:
        The program will continuously control the motor's speed and direction, alternating between different speeds and directions every second.
        Observe the motor's behavior to ensure that it responds correctly to changes in speed and direction.

By following these steps, you can test the provided code on your Raspberry Pi directly and verify that it effectively controls the DC motor connected to GPIO pins. Make sure to double-check your wiring and GPIO pin assignments to avoid any hardware issues.

To connect a DC motor to a Raspberry Pi, you typically need a motor driver circuit such as the L298N or L293D. These motor drivers provide bidirectional control and help protect the Raspberry Pi's GPIO pins from potential damage due to high current draw from the motor.

Here's a general overview of how to connect a DC motor to a Raspberry Pi using an L298N motor driver:

    Motor Driver Connections:
        Connect the power supply (VCC1) of the motor driver to the Raspberry Pi's 5V pin or an external 5V power source.
        Connect the ground (GND1) of the motor driver to the Raspberry Pi's ground (GND) pin.
        Connect the motor's positive terminal (usually labeled "+") to the motor driver's OUT1 terminal.
        Connect the motor's negative terminal (usually labeled "-") to the motor driver's OUT2 terminal.

    Control Connections:
        Connect a PWM (Pulse Width Modulation) pin from the Raspberry Pi (e.g., GPIO pin 18) to the ENA (Enable A) input of the motor driver. This pin controls the motor speed through PWM.
        Connect two GPIO pins from the Raspberry Pi (e.g., GPIO pins 17 and 27) to the IN1 and IN2 inputs of the motor driver. These pins control the motor's direction.

    Power Supply Connections (if needed):
        If the motor requires a higher voltage or current than the Raspberry Pi can provide, connect an external power supply (e.g., a battery pack or a separate power adapter) to the motor driver's VCC2 and GND2 terminals. Make sure to connect the ground of the external power supply to the Raspberry Pi's ground (GND) as well to ensure a common ground reference.

    Additional Connections (if needed):
        Some motor drivers may have additional features such as current sensing or braking. Consult the datasheet of your motor driver for any additional connections required.

    Secure Connections:
        Ensure all connections are securely made and there are no loose wires that could cause a short circuit.

Once the connections are made, you can use the provided C++ code to control the motor's speed and direction from your Raspberry Pi. Make sure to adjust the GPIO pin numbers in the code according to your wiring configuration.
*/

#include <iostream>
#include <wiringPi.h>

#define PWM_PIN 18 // PWM pin connected to motor driver (e.g., L298N)
#define DIR_PIN1 17 // Direction pin 1
#define DIR_PIN2 27 // Direction pin 2

// Initialize motor control pins
void initMotorPins() {
    pinMode(PWM_PIN, PWM_OUTPUT);
    pinMode(DIR_PIN1, OUTPUT);
    pinMode(DIR_PIN2, OUTPUT);
}

// Control motor speed and direction
void controlMotor(int speed, bool forward) {
    if (forward) {
        digitalWrite(DIR_PIN1, HIGH);
        digitalWrite(DIR_PIN2, LOW);
    } else {
        digitalWrite(DIR_PIN1, LOW);
        digitalWrite(DIR_PIN2, HIGH);
    }
    pwmWrite(PWM_PIN, speed);
}

int main() {
    if (wiringPiSetupGpio() == -1) {
        std::cerr << "Error: WiringPi initialization failed." << std::endl;
        return 1;
    }

    initMotorPins();

    int speed = 100; // Set initial speed (0-1023)
    bool forward = true; // Set initial direction

    while (true) {
        // Control motor speed and direction
        controlMotor(speed, forward);

        // Wait for a short duration before changing speed/direction
        delay(1000);

        // Change speed and direction
        speed = (speed + 100) % 1024; // Increase speed by 100 (0-1023)
        forward = !forward; // Toggle direction
    }

    return 0;
}