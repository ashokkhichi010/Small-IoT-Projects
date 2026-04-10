# NodeMCU LED Test

## Overview

This sketch runs a simple LED chase pattern on a NodeMCU-style board. It turns LEDs on one by one in the forward direction, then steps back in the reverse direction.

## Files

- `nodemcu_led_test.ino`: Main Arduino sketch.
- `flow-diagram.svg`: Visual summary of the control flow.

## Hardware used by the sketch

- NodeMCU ESP8266 or similar board
- Four LEDs
- Four current-limiting resistors

## Pin list in the current sketch

The sketch declares:

```cpp
int leds[] = {3,4,5,6};
```

These are raw pin numbers as written in the code. Confirm how your selected ESP8266 board package maps those values before wiring the LEDs.

## Behavior

- `setup()` loops through the LED array and configures each entry as an output.
- `loop()` runs a forward LED chase.
- It then runs a reverse chase back toward the beginning of the array.
- Each LED pulse uses `delay(150)`.

## Upload and test

1. Open `nodemcu_led_test.ino` in the Arduino IDE.
2. Select the correct ESP8266 board profile.
3. Upload the sketch.
4. Watch the LED sequence and confirm the expected chase effect.

## Important implementation notes from the current sketch

- The array contains four elements, but both `for` loops use `i < 5` during parts of execution. That means the current sketch accesses one position beyond the defined array. This documentation keeps the code unchanged, but the behavior should be treated carefully during testing.
- Pin `6` on ESP8266-based boards is commonly tied to flash memory on many modules. If your specific hardware exposes it differently, verify that first; otherwise, do not assume it is a safe general-purpose LED output.
- The reverse loop goes from index `3` down to `1`, so index `0` is skipped on the return path.

## When to use this project

Choose this sketch as a quick smoke test for LED outputs and visible timing on a NodeMCU-based setup. It is a good starting point for learning GPIO sequencing, but it should be reviewed carefully before using it as a production wiring reference.
