# Reactive Obstacle Avoidance Robot

## Overview

This sketch drives a two-motor robot car using an ultrasonic distance sensor mounted on a servo. The car moves forward when the path is clear, slows down as an obstacle gets closer, scans left and right when the front distance drops below the braking range, and then biases the motors to turn toward the side with more open space.

## Files

- `reactive_obstacle_avoidance_robot.ino`: Main Arduino sketch.
- `flow-diagram.svg`: Visual summary of the control flow.

## Hardware used by the sketch

- Arduino Uno, Nano, or a compatible 5 V board
- HC-SR04 ultrasonic distance sensor
- Servo motor for sensor scanning
- L298N, L293D, or similar motor driver
- Two DC motors with a differential-drive chassis
- External motor power source

## Pin mapping

| Function | Pin |
| --- | --- |
| Ultrasonic TRIG | D9 |
| Ultrasonic ECHO | D10 |
| Motor IN1 | D2 |
| Motor IN2 | D3 |
| Motor IN3 | D4 |
| Motor IN4 | D5 |
| Motor ENA | D11 |
| Motor ENB | D12 |
| Servo signal | D6 |

## Runtime behavior

- The sketch measures front distance with `getDistance()`.
- If the path is clear, it sets `targetSpeed` to `HIGHEST_SPEED` which is `200`.
- If the obstacle is inside the braking zone, it reduces the target speed and starts a non-blocking left/right scan.
- The scan moves the servo to one side, samples distance, moves to the other side, samples again, then compares the two readings.
- The car turns by driving the left and right motors at different speeds instead of fully stopping for a pivot turn.
- The main loop repeats continuously without long blocking delays in the steering logic.

## Thresholds in the current code

| Constant | Value | Meaning |
| --- | --- | --- |
| `BREAK_DIST` | `150` | Distance below which scanning and braking behavior begins |
| `STOP_DIST` | `20` | Distance at or below which the target speed becomes zero |
| `HIGHEST_SPEED` | `200` | Maximum target speed for clear-path travel |

## Main functions

- `getDistance()`: Sends the ultrasonic trigger pulse and converts echo time to centimeters.
- `setMotor(left, right)`: Writes PWM values and sets both motors to forward direction.
- `updateSpeed()`: Smoothly ramps `currentSpeed` toward `targetSpeed`.
- `scanEnvironment(direction)`: Moves the servo, captures left and right distances, and returns a preferred turn direction.
- `loop()`: Coordinates distance reading, speed adjustment, scanning, and turning.

## Upload and test

1. Open `reactive_obstacle_avoidance_robot.ino` in the Arduino IDE.
2. Select the correct board and serial port.
3. Install the built-in `Servo` library if your environment does not already include it.
4. Upload the sketch.
5. Power the motors and servo from a supply that can handle current spikes.
6. Open Serial Monitor at `9600` baud to watch distance, speed, scan state, and chosen direction.

## Expected serial output

The sketch prints:

- Current measured distance
- Current speed value
- Scan state transitions
- Selected turn direction

This is useful for confirming whether the robot is staying in clear-path mode or entering the scan-and-turn branch.

## Hardware notes

- Use a shared ground between the Arduino, motor driver, sensor, and external power source.
- A servo can draw enough current to brown out the board if powered directly from a weak 5 V rail.
- Motors can inject noise into the system, so short wires and basic filtering help.

## Important implementation notes from the current sketch

- `ENB` is assigned to pin `D12`. On many Arduino Uno/Nano boards, `D12` is not PWM-capable. If you use those boards, review your motor driver wiring strategy before relying on variable speed on that channel.
- The clear-path branch sets the servo to `0` degrees. If your sensor is physically centered at another angle, adjust your mechanical mounting or treat that as a calibration point when testing.
- The scan logic uses non-blocking timing, but the ultrasonic read itself still depends on `pulseIn()`.

## When to use this project

Choose this sketch when you want a more advanced obstacle-avoidance demo than a simple stop-and-turn robot, especially if you want visible scanning behavior and smoother speed transitions.
