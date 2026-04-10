# Obstacle Avoidance Using IR

## Overview

This sketch runs a differential-drive robot car with two IR obstacle sensors. It uses a simple state machine to move forward, stop when an obstacle is detected, reverse for a short time, choose a turn direction, then continue moving.

## Files

- `obstacle_avoidance_using_IR.ino`: Main Arduino sketch.
- `flow-diagram.svg`: Visual summary of the control flow.

## Hardware used by the sketch

- Arduino Uno, Nano, or compatible board
- Two IR obstacle sensors
- L298N, L293D, or similar motor driver
- Two DC motors and a chassis
- External power source for motors

## Pin mapping

| Function | Pin |
| --- | --- |
| IR left sensor | D6 |
| IR right sensor | D7 |
| Motor IN1 | D2 |
| Motor IN2 | D3 |
| Motor IN3 | D4 |
| Motor IN4 | D5 |
| Motor ENA | D9 |
| Motor ENB | D10 |

## State machine used in the current code

| State | Purpose |
| --- | --- |
| `MOVE` | Accelerate and drive forward while both sensors are clear |
| `STOP` | Ramp speed down to zero |
| `REVERSE` | Drive backward for about `800 ms` |
| `TURN` | Drive a short corrective turn for about `500 ms` |

## Runtime behavior

- The sketch reads both IR sensors using `readIR()`.
- A LOW reading is treated as an obstacle.
- If both sensors are clear, the robot ramps toward `MAX_SPEED = 180`.
- If either sensor sees an obstacle, the robot enters the `STOP` state.
- Once speed reaches zero, the robot reverses.
- After reversing, it chooses the turn direction:
  - obstacle on left only -> turn right
  - obstacle on right only -> turn left
  - both blocked or ambiguous -> default right
- After the timed turn, it returns to `MOVE`.

## Main functions

- `setMotor(left, right, forward)`: Drives the motor driver in forward or reverse mode.
- `stopMotor()`: Writes zero PWM to both motor channels.
- `updateSpeed()`: Smoothly ramps speed up or down.
- `readIR(leftObs, rightObs)`: Samples both IR sensors and converts them into obstacle booleans.
- `loop()`: Runs the state machine.

## Upload and test

1. Open `obstacle_avoidance_using_IR.ino` in the Arduino IDE.
2. Select the correct board and serial port.
3. Upload the sketch.
4. Place the robot on a clear surface and power the motor driver correctly.
5. Open Serial Monitor at `9600` baud to verify left sensor, right sensor, and current state output.

## Serial monitor output

The sketch prints:

- `L:` left obstacle state
- `R:` right obstacle state
- `State:` current state-machine mode

This makes it easy to see whether the robot is stopping because of the left sensor, right sensor, or both.

## Integration notes

- The code assumes the IR modules output LOW when an obstacle is detected. Some modules are wired the opposite way, so test sensor polarity before troubleshooting motion.
- The turn behavior is timed rather than distance-based, so turning accuracy depends on speed, wheel traction, and battery voltage.
- A shared ground between the Arduino and motor driver is required.

## When to use this project

Choose this sketch when you want a simple and understandable autonomous robot based on discrete obstacle sensors instead of a scanning ultrasonic module.
