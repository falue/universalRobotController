# Universal Robot Control (RX/TX)

Based on James Bruton:
https://github.com/XRobots/RemoteDSM


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