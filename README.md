# Directional-DC-Motor-Control-with-Safety-Feedback

## Overview

This project implements a **48V bidirectional DC motor controller** using an **Arduino** and a discrete **MOSFET H-Bridge** simulated in **Proteus**. The controller provides forward, reverse, and stop operation with PWM-based speed control while incorporating safety mechanisms to prevent shoot-through and hardware damage. A quadrature rotary encoder is used for real-time position and direction feedback.

---

## Features

* Full H-Bridge using **P-channel MOSFETs (High Side)** and **N-channel MOSFETs (Low Side)**
* Bidirectional motor control (Clockwise / Stop / Counterclockwise)
* PWM-based speed control using a potentiometer
* Shoot-through and over-current protection
* Immediate shutdown of all MOSFET gate signals during fault conditions
* Real-time rotary encoder position and direction monitoring
* Serial Monitor display of motor shaft angle (with respect to the positive X-axis)
* Complete simulation in Proteus with waveform analysis

---

## Hardware Components

* Arduino Uno
* 48V DC Motor
* Quadrature Rotary Encoder
* P-Channel MOSFETs (High Side)
* N-Channel MOSFETs (Low Side)
* Potentiometer
* Three-Position Direction Switch
* Current Sensor / Current Detection Circuit
* 48V DC Power Supply

---

## Control Inputs

| Input         | Function                  |
| ------------- | ------------------------- |
| Position 1    | Clockwise Rotation        |
| Position 2    | Stop                      |
| Position 3    | Counterclockwise Rotation |
| Potentiometer | PWM Speed Control         |

---

## Safety Mechanism

The controller continuously monitors motor current. If the measured current exceeds the predefined threshold:

* A fault condition is detected.
* The Arduino immediately disables all MOSFET gate signals.
* The H-Bridge is turned off to eliminate shoot-through.
* The motor is safely stopped until the fault is cleared.

---

## Feedback System

A quadrature rotary encoder is used to:

* Detect rotation direction
* Measure shaft position
* Calculate the rotor angle
* Display the angle in real time through the Arduino Serial Monitor

---

## Simulation Results

The Proteus simulation verifies:

* Correct H-Bridge switching
* PWM gate-drive signals
* Motor current waveform
* Direction reversal
* Encoder feedback
* Shoot-through protection under fault conditions

---

## Software Used

* Arduino IDE
* Proteus Design Suite

---

## Concepts Demonstrated

* Embedded Systems
* PWM Motor Control
* H-Bridge Design
* Power Electronics
* MOSFET Switching
* Shoot-Through Protection
* Over-Current Detection
* Rotary Encoder Interfacing
* Fault Detection
* Embedded C Programming

---

## Author

**Krish**
B.Tech, Electronics Engineering
Indian Institute of Technology (BHU), Varanasi
