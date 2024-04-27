# Universal Robot Control (RX/TX)

Based on James Bruton:
https://github.com/XRobots/RemoteDSM


## OrangeRx Receiver re-programming
As the Windows software
["rx_secure_configurator"](https://cdn-global-hk.hobbyking.com/media/file/r/x/rx_secure_configurator.zip?_gl=1*g1ywqd*_ga*MTM1ODE1NzExLjE3MTE0MDI5MjU.*_ga_5W5MJE4N6Q*MTcxNDIxNzU1Ni4xMS4xLjE3MTQyMTc2MTguNTkuMC4w)
for the
[receiver](https://hobbyking.com/en_us/orangerx-rr12rdts-receiver-with-s-link-dsm2-dsmx-compatible.html?___store=en_us)
to set some settings on the receiver is very buggy, buy the
[OrangeTX Program box](https://hobbyking.com/en_us/orangerx-program-box-for-r620x-r1220x-v3-rr12rdts-receivers.html?___store=en_us).
1. Connect the jumper to power the receiver from the program box to pin 1 and 2.
2. Set the "out type" from default "SBus" to "iBUS"
3. ~(optional) Set the *FailSafe" to "no packet" to be able to detect signal loss on the receiver~ Doesn't work!


## OrangeRx Binding Process
1. Power off remote.
2. Power on robot receiver. Its LED flashes fast yellow to indicate that there is no connection.
2. Press "Bind" button on transmitter.
3. Power on remote (!); keep "Bind" button pressed.
4. remote beeps three times; robot receiver stops flashing and has now a continous light. congrats.
5. From here on out, connection is established.

📝 NOTE: Red LED on remote (on the transmitter) does not turn on if no signal is sent to the PPM pin.

📝 NOTE: Always power on robot receiver first, then remote.

📝 NOTE: If turned off remote while robot receiver is on, restart robot receiver as well to reset connection.
Turning off robot receiver while remote is still on, restarting robot receiver again auto connects again.