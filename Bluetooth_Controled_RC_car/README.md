# Bluetooth Controled RC Car

## Overview

This sketch controls a two-motor RC car over a Bluetooth serial link. It listens for single-character commands and converts them into forward, reverse, turning, stop, and diagonal driving patterns.

## Files

- `Bluetooth_Controled_RC_car.ino`: Main Arduino sketch.
- `flow-diagram.svg`: Visual summary of the control flow.

## Hardware used by the sketch

- Arduino Uno, Nano, or compatible board
- HC-05, HC-06, or similar Bluetooth serial module
- L298N, L293D, or similar motor driver
- Two DC motors and chassis
- External motor supply

## Pin mapping

| Function | Pin |
| --- | --- |
| Bluetooth RX on Arduino | D2 |
| Bluetooth TX on Arduino | D3 |
| Motor IN1 | D4 |
| Motor IN2 | D5 |
| Motor IN3 | D6 |
| Motor IN4 | D7 |
| Motor ENA | D9 |
| Motor ENB | D10 |

The sketch creates `SoftwareSerial BT(2, 3)`, so the Arduino receives Bluetooth data on pin `2` and transmits on pin `3`.

## Supported commands

| Command | Action |
| --- | --- |
| `F` | Forward |
| `B` | Backward |
| `L` | Left |
| `R` | Right |
| `S` | Stop |
| `G` | Forward-left |
| `I` | Forward-right |
| `H` | Backward-left |
| `J` | Backward-right |

## Behavior

- The sketch starts both `BT` and `Serial` at `9600` baud.
- When a Bluetooth byte is available, it reads one character and prints it to the hardware serial port.
- A `switch` statement selects the corresponding motor function.
- All motion routines use `speedVal = 180`, with diagonal commands reducing one side to half speed.

## Main functions

- `forward()`, `backward()`, `left()`, `right()`: Standard directional movement.
- `forwardLeft()`, `forwardRight()`, `backwardLeft()`, `backwardRight()`: Differential-speed diagonal movement.
- `stopCar()`: De-energizes all motor direction pins.

## Upload and test

1. Open `Bluetooth_Controled_RC_car.ino` in the Arduino IDE.
2. Select the correct board and serial port.
3. Upload the sketch.
4. Pair your phone or Bluetooth terminal with the module.
5. Send the supported command letters one at a time.
6. Open Serial Monitor at `9600` baud if you want to verify the received characters.

## Wiring notes

- Bluetooth serial wiring must be crossed: module TX -> Arduino D2, module RX <- Arduino D3.
- Many Bluetooth modules expect a lower voltage on their RX input than a 5 V Arduino pin provides. Use a divider or appropriate level protection when needed.
- The sketch does not include a timeout or failsafe; the car continues the last commanded motion until a new command is received.

## When to use this project

Choose this sketch when you want a straightforward Bluetooth car that can be controlled from a serial-terminal app or a custom remote-control app that sends single-letter commands.
