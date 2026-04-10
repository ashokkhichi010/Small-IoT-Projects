# Distance Indicator With LED

## Overview

This sketch measures distance with an HC-SR04 ultrasonic sensor and uses three LEDs to show how close an object is. It gives steady green for far distance, blinking yellow for medium distance, and fast blinking red for near distance.

## Files

- `distance_indicator_with_LED.ino`: Main Arduino sketch.
- `flow-diagram.svg`: Visual summary of the control flow.

## Hardware used by the sketch

- Arduino Uno, Nano, or compatible board
- HC-SR04 ultrasonic sensor
- One green LED
- One yellow LED
- One red LED
- Current-limiting resistors for each LED

## Pin mapping

| Function | Pin |
| --- | --- |
| Ultrasonic TRIG | D9 |
| Ultrasonic ECHO | D10 |
| Green LED | D2 |
| Yellow LED | D3 |
| Red LED | D4 |

## Behavior in the current sketch

| Distance range | Output |
| --- | --- |
| Invalid reading or above 400 cm | Print `Out of range` and skip LED update |
| Greater than 70 cm | Green LED ON |
| Greater than 30 cm and up to 70 cm | Yellow LED blinking every 300 ms |
| 30 cm or less | Red LED blinking every 100 ms |

## How it works

- `getDistance()` triggers the ultrasonic sensor and converts echo time to centimeters.
- Invalid readings are filtered by returning `-1`.
- `setLEDs()` provides a simple way to update all three LEDs together.
- The main loop uses `millis()` for blinking, so the yellow and red blinking logic is non-blocking.
- Distance is also printed to Serial Monitor at `9600` baud.

## Upload and test

1. Open `distance_indicator_with_LED.ino` in the Arduino IDE.
2. Select the correct board and serial port.
3. Upload the sketch.
4. Open Serial Monitor at `9600` baud.
5. Move an object closer and farther from the sensor to confirm the LED thresholds.

## Practical notes

- The sketch assumes standard active-HIGH LEDs. If you use LED modules with different polarity, adapt the wiring expectations during testing.
- Because the code returns immediately on invalid reads, the LEDs will remain in their previous state until the next valid reading.
- The ultrasonic timeout is set to `30000` microseconds, and the code rejects anything reported as zero or greater than 400 cm.

## When to use this project

Choose this sketch when you want a simple visual distance indicator for a demo panel, parking aid prototype, or sensor-learning exercise.
