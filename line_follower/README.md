# Line Follower

## Overview

This sketch controls a simple two-sensor line-following robot. It reads left and right IR sensors and decides whether to drive forward, turn left, turn right, or stop.

## Files

- `line_follower.ino`: Main Arduino sketch.
- `flow-diagram.svg`: Visual summary of the control flow.

## Hardware used by the sketch

- Arduino Uno, Nano, or compatible board
- Two IR line-tracking sensors
- L298N, L293D, or similar motor driver
- Two DC motors and a chassis
- External motor supply

## Pin mapping

| Function | Pin |
| --- | --- |
| Motor IN1 | D4 |
| Motor IN2 | D5 |
| Motor IN3 | D6 |
| Motor IN4 | D7 |
| Motor ENA | D9 |
| Motor ENB | D10 |
| Left sensor | A0 |
| Right sensor | A1 |

## Decision logic in the current sketch

| Left sensor | Right sensor | Action |
| --- | --- | --- |
| `0` | `0` | Move forward |
| `1` | `0` | Turn left |
| `0` | `1` | Turn right |
| `1` | `1` | Stop |

## How it works

- `setupMotors()` configures all motor-control pins.
- `lineFollower()` reads the two sensor values with `digitalRead()`.
- The function immediately chooses one of four motor actions based on the sensor combination.
- `loop()` repeatedly calls `lineFollower()` with no additional timing logic.

## Upload and test

1. Open `line_follower.ino` in the Arduino IDE.
2. Select the correct board and serial port.
3. Upload the sketch.
4. Place the robot over your test track and power the motors.
5. Adjust sensor height and alignment until the action pattern matches the table above.

## Practical notes

- The current logic assumes the sensor modules produce LOW when the line is under the sensor. Many line sensors can be tuned or may behave the opposite way, so confirm the polarity on your hardware.
- The sketch uses `digitalRead()` on `A0` and `A1`, which is acceptable on common Arduino Uno/Nano class boards because those analog pins can also act as digital inputs.
- Motion speed is fixed at `150` in the current code.

## When to use this project

Choose this sketch when you want a minimal, easy-to-understand line follower without PID control or sensor calibration code.
