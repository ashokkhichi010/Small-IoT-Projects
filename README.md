# Arduino Projects Index

This README documents only the Arduino sketch projects found in the current workspace during this pass. No non-Arduino folders are included here.

## Included projects

| Project | Board target | Summary | Full docs | Flow |
| --- | --- | --- | --- | --- |
| Reactive Obstacle Avoidance Robot | Arduino Uno/Nano class board | Robot car that uses an ultrasonic sensor on a servo to slow down, scan, and steer around obstacles. | [README](./reactive_obstacle_avoidance_robot/README.md) | [FLOW DIAGRAM](./reactive_obstacle_avoidance_robot/flow-diagram.svg) |
| Obstacle Avoidance Using IR | Arduino Uno/Nano class board | Robot car that reacts to left and right IR obstacle sensors with stop, reverse, and turn states. | [README](./obstacle_avoidance_using_IR/README.md) | [FLOW DIAGRAM](./obstacle_avoidance_using_IR/flow-diagram.svg) |
| Distance Indicator With LED | Arduino Uno/Nano class board | Ultrasonic distance monitor that shows far, medium, and near ranges with green, yellow, and red LEDs. | [README](./distance_indicator_with_LED/README.md) | [FLOW DIAGRAM](./distance_indicator_with_LED/flow-diagram.svg) |
| Distance Based Alarm | NodeMCU / ESP8266 style board | Ultrasonic distance alarm with silent, slow-beep, fast-beep, and continuous alarm ranges. | [README](./distance_based_alarm/README.md) | [FLOW DIAGRAM](./distance_based_alarm/flow-diagram.svg) |
| NodeMCU LED Test | NodeMCU / ESP8266 style board | Basic LED chase test for verifying output pins and timing on a NodeMCU-style board. | [README](./nodemcu_led_test/README.md) | [FLOW DIAGRAM](./nodemcu_led_test/flow-diagram.svg) |
| Bluetooth Controled RC Car | Arduino Uno/Nano class board | Bluetooth-driven RC car that accepts single-character movement commands from a phone app or serial bridge. | [README](./Bluetooth_Controled_RC_car/README.md) | [FLOW DIAGRAM](./Bluetooth_Controled_RC_car/flow-diagram.svg) |
| Line Follower | Arduino Uno/Nano class board | Two-sensor line-following car that steers left or right based on line position. | [README](./line_follower/README.md) | [FLOW DIAGRAM](./line_follower/flow-diagram.svg) |

## Quick comparison

### Mobile robots

- `reactive_obstacle_avoidance_robot`: Best for a more advanced obstacle-avoidance car with speed ramping and servo scanning.
- `obstacle_avoidance_using_IR`: Best for a simpler obstacle-avoidance car using left and right IR sensors.
- `Bluetooth_Controled_RC_car`: Best when manual control from a Bluetooth app is needed.
- `line_follower`: Best for track-following demonstrations.

### Sensor and output demos

- `distance_indicator_with_LED`: Visual distance feedback with LEDs only.
- `distance_based_alarm`: Audible distance feedback with a buzzer.
- `nodemcu_led_test`: Pin-output and LED sequence smoke test.

## Notes from the current sketches

- Most motor-control projects assume an Arduino-compatible motor driver such as L298N or L293D.
- The NodeMCU projects use ESP8266-style pin naming or raw pin numbers, so the exact wiring should be checked against the board package and hardware used.
- `nodemcu_led_test` currently defines four LED pins but loops across five array positions; that is documented in the project README as an implementation note and was not changed here.
- `reactive_obstacle_avoidance_robot` uses `ENB` on pin `12`, which is not PWM-capable on many Uno/Nano boards. The docs call this out so wiring can be planned accordingly.

## How to use these docs

1. Open the project README for hardware, pin map, upload steps, behavior, and project-specific notes.
2. Open the project `flow-diagram.svg` if you want a quick visual of the runtime logic.
3. Upload the matching `.ino` sketch from that project folder in the Arduino IDE or compatible toolchain.
