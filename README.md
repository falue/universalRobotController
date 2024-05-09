# Universal Robot Control (RX/TX)

## Introduction

This repository includes transmitter (TX) and receiver (RX) arduino files for a remote controlled robot of any form.

The transmitter is a custom build to have full control over input mixing.
It depends on a custom PCB, or like a thousand wires.
The receiver end can be a robot or whatever.

> Based on James Brutons RemoteDSM:
> 
> <https://github.com/XRobots/RemoteDSM>
> 
> <https://youtu.be/5BfRg9CUMYI>

# Hardware
## TX
- [Arduino Mega ↗](https://store.arduino.cc/products/arduino-mega-2560-rev3)
- One thousand switches and buttons
- One thousand linear potentiometers
- A custom PCB (files here: [gerber.zip](kicad/universalRobotTx/gerber/gerber.zip) | [kicad](kicad/universalRobotTx))
- A laser cut case (files here: [ai](cad/universal_robot_laser.ai) | [dxf](cad/universal_robot_laser.dxf) | [svg](cad/universal_robot_laser.svg))
- One (or two) [OrangeRX DSMX DSM2 transmitter ↗](https://hobbyking.com/en_us/orangerx-dsmx-dsm2-compatible-2-4ghz-transmitter-module-v1-2.html)

## RX
- [Arduino Leonardo (or UNO) ↗](https://store.arduino.cc/products/arduino-leonardo-with-headers)
- [Arduino Motor Shield Rev3 ↗](https://store.arduino.cc/products/arduino-motor-shield-rev3)
- One  (or two) [OrangeRx RR12RDTS Receiver ↗](https://hobbyking.com/en_us/orangerx-rr12rdts-receiver-with-s-link-dsm2-dsmx-compatible.html)
- [OrangeRx Program box ↗](https://hobbyking.com/en_us/orangerx-program-box-for-r620x-r1220x-v3-rr12rdts-receivers.html)

---

# OrangeRx setup

## OrangeRx Receiver re-programming
As the Windows software "[rx_secure_configurator ↗](https://cdn-global-hk.hobbyking.com/media/file/r/x/rx_secure_configurator.zip?_gl=1*g1ywqd*_ga*MTM1ODE1NzExLjE3MTE0MDI5MjU.*_ga_5W5MJE4N6Q*MTcxNDIxNzU1Ni4xMS4xLjE3MTQyMTc2MTguNTkuMC4w)" for the [receiver ↗](https://hobbyking.com/en_us/orangerx-rr12rdts-receiver-with-s-link-dsm2-dsmx-compatible.html) to set some settings on the receiver is **very** buggy, buy the [OrangeRx Program box ↗](https://hobbyking.com/en_us/orangerx-program-box-for-r620x-r1220x-v3-rr12rdts-receivers.html).
1. Connect the jumper to power the receiver from the program box to pin 1 and 2.
2. Set the "out type" from default "*SBus*" to "*iBUS*"
3. Set the *FailSafe" to send "1500" on all channels when losing connection; to be able to detect signal loss on the receiver


## OrangeRx Binding Process
1. Power off remote.
2. Power on robot receiver. Its LED flashes fast yellow to indicate that there is no connection.
2. Press "Bind" button on transmitter.
3. Power on remote (!); keep "Bind" button pressed.
4. remote beeps three times; robot receiver stops flashing and has now a continous light. congrats.
5. From here on out, connection is established.

> 📝 NOTE: Red LED on remote (on the transmitter) does not turn on if no signal is sent to the PPM pin.
> 
> 📝 NOTE: Always power on robot receiver first, then remote.
> 
> 📝 NOTE: If turned off remote while robot receiver is on, restart robot receiver as well to reset connection.
> Turning off robot receiver while remote is still on, restarting robot receiver again auto connects again.