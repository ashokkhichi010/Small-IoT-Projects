# Distance Based Alarm

## Overview

This sketch runs an ultrasonic distance alarm on a NodeMCU or ESP8266-style board. It measures distance and drives a buzzer with four alert levels: silent, slow beep, fast beep, and continuous tone.

## Files

- `distance_based_alarm.ino`: Main Arduino sketch.
- `flow-diagram.svg`: Visual summary of the control flow.

## Hardware used by the sketch

- NodeMCU ESP8266 or similar board
- HC-SR04 ultrasonic sensor
- Active buzzer or a buzzer circuit compatible with a GPIO output

## Pin mapping

| Function | Pin |
| --- | --- |
| Ultrasonic TRIG | D5 |
| Ultrasonic ECHO | D6 |
| Buzzer | D7 |

## Alert levels in the current code

| Distance range | Buzzer behavior |
| --- | --- |
| Greater than 100 cm | OFF |
| Greater than 50 cm and up to 100 cm | `beep(800)` |
| Greater than 20 cm and up to 50 cm | `beep(300)` |
| 20 cm or less | Constant ON |

The `beep(delayTime)` helper keeps the buzzer HIGH for `100 ms`, then LOW for the configured delay. That means the slow and fast beeps differ mainly in the off-time between pulses.

## How it works

- The main loop triggers the HC-SR04 sensor.
- `pulseIn()` measures the echo time.
- Distance is converted to centimeters and printed to the serial port at `115200` baud.
- The code selects the buzzer mode based on the measured range.

## Upload and test

1. Open `distance_based_alarm.ino` in the Arduino IDE.
2. Select a NodeMCU or the correct ESP8266 board profile.
3. Select the correct serial port and upload.
4. Open Serial Monitor at `115200` baud.
5. Move an object toward the sensor and confirm each buzzer threshold.

## Hardware safety note

The HC-SR04 ECHO pin commonly outputs 5 V. The ESP8266 GPIO pins are not 5 V tolerant. Use a level shifter or voltage divider between ECHO and the board input before testing on real hardware.

## Practical notes

- Because `beep()` uses `delay()`, the loop is intentionally blocking while beeps are being generated.
- If you use a passive buzzer instead of an active one, this sketch will not create tones in the same way because it only switches the pin HIGH and LOW.
- Distance values are printed continuously, which is helpful for threshold tuning.

## When to use this project

Choose this sketch when you want an audible proximity warning on an ESP8266-based board with minimal hardware and straightforward logic.
