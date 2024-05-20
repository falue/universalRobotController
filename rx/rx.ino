#include <IBusBM.h>  // https://github.com/bmellink/IBusBM
#include <Servo.h>

IBusBM IBus; // IBus object

Servo servoX;
Servo servoY;

// Options
bool enableDrive = false;          // Set by switch 2
bool enableHeadMovements = false;  // Set by switch 1
bool fakeRemoteInputs = false;     // If you do not have a RX connected, try this. Generates ramp-ups and -downs of joystiuck movement.
bool forceDisableMotors = false;    // Disable effective motor control, but keep calculations & serial prints

// Servos
int servoXPin = 2;
int servoYPin = 10;

// DC Motors
int directionPinA = 13;
int pwmPinA = 11;
int brakePinA =  8;

int directionPinB = 12;
int pwmPinB = 3;
int brakePinB =9;

// Remote channels
int joystickLX = 1500;
int joystickLY = 1500;
int joystickLZ = 1500;
int jostickRX = 1500;
int jostickRY = 1500;
int jostickRZ = 1500;
bool joyBtnL = false;
bool joyBtnR = false;
bool enableAcceleratedSmoothing = false;

// Unused btns
bool disableSteering = false;
bool userBtn1 = false;
bool userBtn2 = false;
// bool userBtn3 = false;  // not used
// bool userBtn4 = false;  // not used
// bool userBtn5 = false;  // not used
// bool userBtn6 = false;  // not used
int poti1 = 1500;
int poti2 = 1500;

bool decodedButtons0[4];
bool decodedButtons1[4];

// Smoothing servos
float smoothedValueX = float(jostickRX);
float smoothedValueY = float(jostickRY);
float smoothedValueZ = float(jostickRZ);

float currentSmoothedX = smoothedValueX;
float currentSmoothedY = smoothedValueY;

// Limit the max speed of the robot
// 0-254 *or* 0-100. This is up for dabate. The latter is mentioned in the docs of the
// motor shield r3 but a weird thing, usually things like that are 0-254.
int maxSpeed = 100;  // Changed by poti1
int minSpeed = 33;   // Below this, the motors do not turn bc. of friction and not being spherical cows in space
float headMovementSmoothing = 0.01;

// fakeRemoteInputs
int directionX = 1, directionY = 1, directionZ = 1;
int phase = 0;
int step = 2;
const int startValue = 1000;
const int endValue = 2000;

void setup() {
  delay(1666);

  Serial.begin(115200);
  
  // Establish IBus connection to receiver
  //   Change to Serial1 = D0 (or Serial2 or 3 for on ard mega or so) port when required
  //   The servo library conflicts with the interrupts used by the IBus library -
  //   Therefore, use second argument "IBUSBM_NOTIMER" to call the IBus.loop() function manually in the main loop
  IBus.begin(Serial1, IBUSBM_NOTIMER);

  // Attach head servos
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  // Define motor pins
  pinMode(directionPinA, OUTPUT);
  pinMode(pwmPinA, OUTPUT);
  pinMode(brakePinA, OUTPUT);

  pinMode(directionPinB, OUTPUT);
  pinMode(pwmPinB, OUTPUT);
  pinMode(brakePinB, OUTPUT);
}

void loop() {
  if(!fakeRemoteInputs) {
    readChannels();
  } else {
    fakeJoystickValues();
  }

  detectLossOfSignal();

  debugPrints();

  drive(joystickLX, joystickLY, joystickLZ);

  if(enableDrive) {
    if(joyBtnL) {
      quickturn("joyBtnL", -180);
    }
    if(joyBtnR) {
      quickturn("joyBtnR", 180);
    }
    if(userBtn1) {
      quickturn("userBtn1", -5);
    }
    if(userBtn2) {
      quickturn("userBtn2", 5);
    }
  }
  

  if(enableHeadMovements) {
    if(!servoX.attached()) {
      servoX.attach(servoXPin);
      servoY.attach(servoYPin);
    }
    headMovement(jostickRX, jostickRY, jostickRZ);
  } else if(servoX.attached()) {
    servoX.detach();
    servoY.detach();
  }

  Serial.println("");
  // delay(5);  // Do not delay because IBus.loop() must be called as fast as possible
}


void fakeJoystickValues() {
    if(phase == 0 || phase == 3 || phase >= 4) {
      // Update Y
      if (joystickLY >= endValue || joystickLY <= startValue) {
          directionY *= -1;  // Reverse the direction
      }
      joystickLY += directionY * step;
      
      if(joystickLY <= startValue) {
        joystickLY = 1500;
        directionY = 1;
        phase++;
        delay(2000);
      }
    }

    if(phase == 1 || phase == 3 || phase >= 4) {
      // Update X
      if (joystickLX >= endValue || joystickLX <= startValue) {
          directionX *= -1;  // Reverse the direction
      }
      joystickLX += directionX * step;

      if(joystickLX <= startValue) {
        joystickLX = 1500;
        directionX = 1;
        phase++;
        delay(2000);
      }
    }

    if(phase == 2 || phase >= 4) {
      // Update Z
      if (joystickLZ >= endValue || joystickLZ <= startValue) {
          directionZ *= -1;  // Reverse the direction
      }
      joystickLZ += directionZ * step;
      
      if(joystickLZ <= startValue) {
        joystickLZ = 1500;
        directionZ = 1;
        phase++;
        delay(2000);
      }
    }

    String dirArrow = "";

    if(joystickLY > 1500) dirArrow += "▲";
    if(joystickLY < 1500) dirArrow += "▼";

    if(joystickLX > 1500) dirArrow += "►";
    if(joystickLX < 1500) dirArrow += "◄";

    if(joystickLZ > 1500) dirArrow += "⤵";
    if(joystickLZ < 1500) dirArrow += "⤴";

    // Output the current values and mixes to the Serial Monitor
    Serial.print("LX: "); Serial.print(joystickLX);
    Serial.print("\tLY: "); Serial.print(joystickLY);
    Serial.print("\tLZ: "); Serial.print(joystickLZ);
    Serial.print("\tsteering: ");
    Serial.print(dirArrow);
}

void readChannels() {
  // Call internal loop function to update the communication to the receiver.
  //   Needed if IBus.begin(); is called with second parameter "IBUSBM_NOTIMER"
  IBus.loop();
  int correction = -19;  // Somehow all the values are shifted 11-26 points (weighted median ~19)

  /*
  Sent by TX1:
    ch0: joystickLX
    ch1: joystickLY
    ch2: joystickLZ
    ch3: joystickRX
    ch4: joystickRY
    ch5: joystickRZ
    ch6: encodedButtons0 = {0: toggleSwitch1 1: toggleSwitch2 2: toggleSwitch3 3: toggleSwitch4}
    ch7: encodedButtons1 = {0: joyBtnL       1: joyBtnR       2: userBtn1      3: userBtn2}
    ch8: poti1
    ch9: poti2
  
  Sent by TX2 (if enabled):
    ch10: poti3
    ch11: poti4
    ch12: poti5
    ch13: poti6
    ch14: encodedButtons2 = {0: toggleSwitch5 1: toggleSwitch6 2: userBtn3  3: userBtn4}
    ch15: encodedButtons3 = {0: userBtn5      1: userBtn6      2: userBtn7  3: userBtn8}
    ch16: encodedButtons4 = {0: userBtn9      1: userBtn10     2: userBtn11 3: userBtn12}
    ch17: encodedButtons5 = {0: userBtn13     1: userBtn14     2: userBtn15 3: userBtn18}
    ch18: encodedButtons6 = {0: userBtn19     1: sysBtn1       2: sysBtn2   3: sysBtn3}
    ch19: 1500 (NC - not connected)
  */

  // Get the latest IBus data from cached data
  //   IMPORTANT: Somehow, some (?) channels are reordered by the TX or (!) RX
  joystickLY = IBus.readChannel(0) + correction;
  joystickLZ = IBus.readChannel(1) + correction;
  joystickLX = IBus.readChannel(2) + correction;
  jostickRX = IBus.readChannel(3) + correction;
  jostickRY = IBus.readChannel(4) + correction;
  jostickRZ = IBus.readChannel(5) + correction;
  
  // Add bool array to function because memory leaks
  decodeButtons(IBus.readChannel(6) + correction, decodedButtons0);
  decodeButtons(IBus.readChannel(7) + correction, decodedButtons1);

  enableDrive = decodedButtons0[0];
  enableHeadMovements = decodedButtons0[1];
  enableAcceleratedSmoothing = decodedButtons0[2];
  disableSteering = decodedButtons0[3];

  joyBtnL = decodedButtons1[0];
  joyBtnR = decodedButtons1[1];
  userBtn1 = decodedButtons1[2];
  userBtn2 = decodedButtons1[3];

  poti1 = IBus.readChannel(8) + correction;
  maxSpeed = map(poti1, 1000,2000, minSpeed,254);

  poti2 = IBus.readChannel(9) + correction;
  headMovementSmoothing = map(poti2, 1000,2000, 1,5000) / 100000.0;  // 0.01 is good, but can be less or up to 1
}

void debugPrints() {
  Serial.print("\tLX: ");
  Serial.print(joystickLX);
  Serial.print("\tLY: ");
  Serial.print(joystickLY);
  Serial.print("\tLZ: ");
  Serial.print(joystickLZ);
  Serial.print("\tRX: ");
  Serial.print(jostickRX);
  Serial.print("\tRY: ");
  Serial.print(jostickRY);
  Serial.print("\tRZ: ");
  Serial.print(jostickRZ);
  Serial.print("\tJBtnL: ");
  Serial.print(joyBtnL);
  Serial.print("\tJBtnR: ");
  Serial.print(joyBtnR);
  Serial.print("\tenDrive: ");
  Serial.print(enableDrive);
  Serial.print("\tenHead: ");
  Serial.print(enableHeadMovements);
  Serial.print("\tswitch3: ");
  Serial.print(enableAcceleratedSmoothing);
  Serial.print("\tswitch4: ");
  Serial.print(disableSteering);
  Serial.print("\tBtn1: ");
  Serial.print(userBtn1);
  Serial.print("\tBtn2: ");
  Serial.print(userBtn2);
  Serial.print("\tpot1: ");
  Serial.print(poti1);
  Serial.print("\tpot2: ");
  Serial.print(poti2);

  Serial.print("\tmaxSpeed: ");
  Serial.print(maxSpeed);
  Serial.print("\theadSmooth: ");
  Serial.print(headMovementSmoothing);
}

int calculateMotorSpeed(int Y, int X, int Z, char motorSide) {
  // TODO: Z is ignored now
  float mixer = 1.0;
  float minMixer = 0.5;
  // if full forward/backward and left, use 0.5
  // if full left, use 1.0
  mixer = 2.0 - map((abs(Y)+abs(X))*100, 0,maxSpeed*100, minMixer*100,100) / 100.0;
  mixer = clamp(mixer, 0.1, 1.0);
  
  int leftMotor = Y + int(X*mixer);
  int rightMotor = Y - int(X*mixer);
  
  leftMotor = clamp(leftMotor, -maxSpeed, maxSpeed);
  rightMotor = clamp(rightMotor, -maxSpeed, maxSpeed);
  
  if (motorSide == 'L') {
    Serial.print("\tmixer: ");
    Serial.print(mixer);
    return leftMotor;
  } else {
    return rightMotor;
  }
}

void drive(int X, int Y, int Z) {
  /* Terack movement */
  int deathZone = 30;  // 35, 50 works too
  // If walues chang only very little, nothing is being controlled, i.e. robot should be idling
  bool idle = isInDeathZone(X, 1500, deathZone) && isInDeathZone(Y, 1500, deathZone) && isInDeathZone(Z-165, 1500, deathZone);  // Z-165 because cheap joystick & cannot be trimmed

  // Values between 1000 and 2000
  X = clampMap(X, 1000,2000, -maxSpeed,maxSpeed);
  Y = clampMap(Y, 1000,2000, -maxSpeed,maxSpeed);
  Z = clampMap(Z, 1000,2000, maxSpeed,-maxSpeed);  // invert Z axis for some reason

  if(disableSteering) {
    X = 0;
  }

  // TODO: use Z for something
  /*if(abs(Z-1500) > abs(X-1500)) {
    X = Z < 1500 ? min(X, Z) : max(X, Z);
  }*/

  if(idle || !enableDrive) {
    // Remote is not touched - engange breaks and do nothing
    digitalWrite(brakePinA, HIGH);
    digitalWrite(brakePinB, HIGH);
    analogWrite(pwmPinA, 0);
    analogWrite(pwmPinB, 0);
  } else {
    // Release breaks
    digitalWrite(brakePinA, LOW);
    digitalWrite(brakePinB, LOW);

    // Mix X Y Z together
    // Get values between -maxSpeed and maxSpeed
    int motorL = calculateMotorSpeed(Y, X, Z, 'L');
    int motorR = calculateMotorSpeed(Y, X, Z, 'R');

    // Set direction
    digitalWrite(directionPinA, motorL < 0);  // LOW to reverse
    digitalWrite(directionPinB, motorR < 0);  // LOW to reverse

    Serial.print("\tmotorL: ");
    Serial.print(motorL);
    Serial.print("\tdir_motorL: ");
    Serial.print(motorL < 0 ? "back" : "forward");
    Serial.print("\tmotorR: ");
    Serial.print(motorR);
    Serial.print("\tdir_motorR: ");
    Serial.print(motorR < 0 ? "back" : "forward");

    // Power to the motors
    if(!forceDisableMotors) {
      analogWrite(pwmPinA, abs(motorL));  // abs makes out of -50 +50
      analogWrite(pwmPinB, abs(motorR));  // abs makes out of -50 +50
    }
  }

  Serial.print("\tmotorL: ");
  Serial.print(0);
  Serial.print("\tdir_motorL: ");
  Serial.print("idle");
  Serial.print("\tmotorR: ");
  Serial.print(0);
  Serial.print("\tdir_motorR: ");
  Serial.print("idle");
}


 bool debounce(String btnName) {
  bool btnState = true;
  while(btnState) {
    readChannels();
    if (btnName == "joyBtnL") {
      btnState = joyBtnL;
    } else if (btnName == "joyBtnR") {
      btnState = joyBtnR;
    } else if (btnName == "userBtn1") {
      btnState = userBtn1;
    } else if (btnName == "userBtn2") {
      btnState = userBtn2;
    } else {
      Serial.println("This btn has to be hard coded here to be debounced");
      btnState = false;
    }
    Serial.print(btnName);
    Serial.println(" - wait for btn release");
    delay(1);
  }
}

void quickturn(String btnName, int deg) {
  // On the press of a joystick or user button, make a quickturn left or right
  debounce(btnName);  // Waits for btn release

  // Release breaks
  digitalWrite(brakePinA, LOW);
  digitalWrite(brakePinB, LOW);
  digitalWrite(directionPinA, deg > 0 ? LOW : HIGH);   // LOW to reverse
  digitalWrite(directionPinB, deg < 0 ? LOW : HIGH);   // LOW to reverse
  analogWrite(pwmPinA, 100);
  analogWrite(pwmPinB, 100);
  int durationOfTurn = abs(deg)*2.6;
  Serial.println("Fast turn duration: ");
  Serial.print(durationOfTurn);
  delay(durationOfTurn); // Depends on ground and grip of tracks
}

bool isInDeathZone(int value, int idleValue, int deathZone) {
  bool isBelow = value < idleValue - deathZone;
  bool isAbove = value > idleValue + deathZone;
  return !(isBelow || isAbove);
}

// Function to calculate exponential moving average for a given sensor value
float exponentialMovingAverage(float newValue, float& smoothedValue, float smoothingFactor) {
  // smoothingFactor: 1=no smoothing; 0.0001 = much please yes smoothing but slow
  smoothedValue = (newValue * smoothingFactor) + (smoothedValue * (1 - smoothingFactor));
  return smoothedValue;
}

void headMovement(int X, int Y, int Z) {
  /* Servo Head movement */
  // Values between 1000 and 2000
  // No matter if the stick is leaning halfway in any direction, but its turned
  //   fully, always take the bigger (or smaller) value of Z
  if(abs(Z-1500) > abs(X-1500)) {
    X = Z < 1500 ? min(X, Z) : max(X, Z);
  }

  // Smooth out the signal
  float smoothingX = headMovementSmoothing;  // Depends on loop speed
  float smoothingY = smoothingX/2.0;  // Depends on loop speed

  // If X much greater than smoothedValueX, decrease smoothingX
  //   eg. if moving stick fast, increase responsiveness
  if(enableAcceleratedSmoothing) {
    if(abs(X - smoothedValueX) > 100) {
      smoothingX *= abs(X - smoothedValueX)/10;
    } else if(abs(Y - smoothedValueY) > 100) {
      smoothingY *= abs(Y - smoothedValueY)/10;
    }
    smoothingX = clamp(smoothingX, 0.0, .1);
    smoothingY = clamp(smoothingY, 0.0, .1);
  }

  currentSmoothedX = exponentialMovingAverage(X, smoothedValueX, smoothingX);
  currentSmoothedY = exponentialMovingAverage(Y, smoothedValueY, smoothingY);
  // float currentSmoothedZ = exponentialMovingAverage(Z, smoothedValueZ, 0.1);

  int servoValueX = map(currentSmoothedX, 1000, 2000, 1750, 2300);  // left, right
  servoX.writeMicroseconds(servoValueX);
  // Recenter head vertically
  int servoValueY = map(currentSmoothedY, 1000, 2000, 2050, 1675);  // up, down
  //servoValueY = clamp(servoValueY, 1675, 2050);  // recenter?
  servoY.writeMicroseconds(servoValueY);
}

int clamp(int value, int min, int max) {
   return value > max ? max : value < min ? min : value;
}

float clamp(float value, float min, float max) {
   return value > max ? max : value < min ? min : value;
}

int clampMap(int value, int valueFrom, int valueTo, int from, int to) {
  if(value < valueFrom) value = valueFrom;
  if(value > valueTo) value = valueTo;
  return map(value, valueFrom, valueTo, from, to);
}

void detectLossOfSignal() {
  // TODO: Does not work
  int failsaveValues = joystickLX + joystickLY + joystickLZ + jostickRX + jostickRY + jostickRZ + joyBtnL + joyBtnR + enableDrive + enableHeadMovements;
  int defaultValueSum = 8623;  //  technically: 6*1500 + 4*0, but IRL: 5*1500+1123 (first channel is 1123?!)
  if(failsaveValues == defaultValueSum) {  // Todo: Loss of signal detection somehow. Kind of the same as the idle state?!
    while(failsaveValues == defaultValueSum) {
      Serial.println("Loss of signal - wait for reconnection");
      readChannels();
      failsaveValues = joystickLX + joystickLY + joystickLZ + jostickRX + jostickRY + jostickRZ + joyBtnL + joyBtnR + enableDrive + enableHeadMovements;
      delay(25);
    }
  }
}

// Decode int from 1000 to 2000 and get array of 4 boolean values
bool* decodeButtons(int encodedValue, bool* buttonStates) {
    // Jitter of +/-32 can be handled
    // static bool buttonStates[4];  // Static to preserve state after the function returns

    // Define the exact encoded values for each combination of button states
    int encodedStates[16] = {
        1000, // 0000
        1066, // 0001
        1133, // 0010
        1200, // 0011
        1266, // 0100
        1333, // 0101
        1400, // 0110
        1466, // 0111
        1533, // 1000
        1600, // 1001
        1666, // 1010
        1733, // 1011
        1800, // 1100
        1866, // 1101
        1933, // 1110
        2000  // 1111
    };

    // Find the closest encoded state
    int closestIndex = 0;
    int smallestDifference = abs(encodedValue - encodedStates[0]);
    for (int i = 1; i < 16; i++) {
        int diff = abs(encodedValue - encodedStates[i]);
        if (diff < smallestDifference) {
            smallestDifference = diff;
            closestIndex = i;
        }
    }

    // Decode the closest index into button states
    buttonStates[0] = (closestIndex & 1) != 0;    // Least significant bit
    buttonStates[1] = (closestIndex & 2) != 0;    // Second bit
    buttonStates[2] = (closestIndex & 4) != 0;    // Third bit
    buttonStates[3] = (closestIndex & 8) != 0;    // Most significant bit

    return buttonStates;
}
