#include <IBusBM.h>  // https://github.com/bmellink/IBusBM
#include <Servo.h>

IBusBM IBus; // IBus object

Servo servoX;
Servo servoY;

// Options
bool enableHeadMovements = false;
bool enableDrive = false;
bool fakeRemoteInputs = false;

// Servos
int servoXPin = 5;
int servoYPin = 6;

// DC Motors
int directionPinA = 13;  // 12   CHANGES DIRECTION WHEN UPLAODING because 13 = built in LED
int pwmPinA = 11;  // 3
int brakePinA =  8;  // 9

int directionPinB = 12;  // 13;
int pwmPinB = 3;  // 11;
int brakePinB =9;  //  8;

// Remote channels
int joystickLX = 1500;
int joystickLY = 1500;
int joystickLZ = 1500;
int jostickRX = 1500;
int jostickRY = 1500;
int jostickRZ = 1500;
int joyBtnL = 1500;
int joyBtnR = 1500;
int toggleSwitch1 = 1500;
int toggleSwitch2 = 1500;

// Smoothing servos
float smoothedValueX = float(jostickRX);
float smoothedValueY = float(jostickRY);
float smoothedValueZ = float(jostickRZ);

// Limit the max speed of the robot
// 0-254 *or* 0-100. This is up for dabate. The latter is mentioned in the docs of the
// motor shield r3 but a weird thing, usually things like that are 0-254.
int maxSpeed = 100;

// fakeRemoteInputs
int directionX = 1, directionY = 1, directionZ = 1;
int step = 2;
const int startValue = 1000;
const int endValue = 2000;

void setup() {
  delay(1666);

  Serial.begin(115200);   // remove comment from this line if you change the Serial port in the next line
  // next line somehow makes servo twitch
  IBus.begin(Serial1, IBUSBM_NOTIMER);    // change to Serial1 = D0 (or Serial2 or 3 for on ard mega or so) port when required

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

  if(enableDrive) {
    drive(joystickLX, joystickLY, joystickLZ);
  }

  if(enableHeadMovements) {
    servoX.attach(servoXPin);
    servoY.attach(servoYPin);
    headMovement(jostickRX, jostickRY, jostickRZ);
  } else {
    servoX.detach();
    servoY.detach();
  }

  debugPrints();

  // delay(5);  do not delay because IBus.loop() must be called as fast as possible
}

int phase = 0;

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
    Serial.println("");
}

void readChannels() {
  // Call internal loop function to update the communication to the receiver.
  //   Needed if IBus.begin(); is called with second parameter "IBUSBM_NOTIMER"
  IBus.loop();

  // Get the latest IBus data from cached data
  joystickLX = IBus.readChannel(2);  // get latest value for servo channel 2  // Somehow, these three channels are reordered by the TX or (!) RX
  joystickLY = IBus.readChannel(0);  // get latest value for servo channel 0  // Somehow, these three channels are reordered by the TX or (!) RX
  joystickLZ = IBus.readChannel(1);  // get latest value for servo channel 1  // Somehow, these three channels are reordered by the TX or (!) RX
  jostickRX = IBus.readChannel(3);   // get latest value for servo channel 4
  jostickRY = IBus.readChannel(4);   // get latest value for servo channel 5
  jostickRZ = IBus.readChannel(5);   // get latest value for servo channel 6

  /// WIP
  /// MAYBE GO BACK TO LAST COMMIT because fuck it
  /*
  bool* decodedSwitches = decodeButtons(IBus.readChannel(6));  // toggleSwitch1,toggleSwitch2,toggleSwitch3,toggleSwitch4
  bool* decodedButtons1 = decodeButtons(IBus.readChannel(7));  // joyBtnL,joyBtnR,userBtn1,userBtn2
  bool* decodedButtons2 = decodeButtons(IBus.readChannel(8));  // userBtn3,userBtn4,userBtn5,userBtn6
  Serial.print(IBus.readChannel(6));
  Serial.print(", ");
  Serial.print(IBus.readChannel(7));
  Serial.print(", ");
  Serial.print(IBus.readChannel(8));
  Serial.print(", joyBtnL: ");

  enableDrive = decodedSwitches[0];
  enableHeadMovements = decodedSwitches[1];
  toggleSwitch3 = decodedSwitches[2];
  toggleSwitch4 = decodedSwitches[3];
  joyBtnL = decodedButtons1[0];
  joyBtnR = decodedButtons1[1];
  userBtn1 = decodedButtons1[2];
  userBtn2 = decodedButtons1[3];
  userBtn3 = decodedButtons2[0];
  userBtn4 = decodedButtons2[1];
  userBtn5 = decodedButtons2[2];
  userBtn6 = decodedButtons2[3];
  poti1 = IBus.readChannel(9);  // maxSpeed = map(IBus.readChannel(9), 1000,2000, 20,100);
  
  Serial.print(joyBtnL);
  Serial.print(", joyBtnR: ");
  Serial.print(joyBtnR);
  Serial.print(", enableDrive: ");
  Serial.print(enableDrive);
  Serial.print(", enableHeadMovements: ");
  Serial.print(enableHeadMovements);
  Serial.print(", toggleSwitch3: ");
  Serial.print(toggleSwitch3);
  Serial.print(", toggleSwitch4: ");
  Serial.print(toggleSwitch4);
  */

  joyBtnL = IBus.readChannel(6) > 1750;     // get latest value for servo channel 7
  joyBtnR = IBus.readChannel(7) > 1750;     // get latest value for servo channel 8
  enableDrive = IBus.readChannel(8) > 1750;         // get latest value for servo channel 9  - 1750 becauwse failsafe is 1500
  enableHeadMovements = IBus.readChannel(9) > 1750; // get latest value for servo channel 10 - 1750 becauwse failsafe is 1500
  
  // encodedSwitches, encodedButtons1, encodedButtons2, poti1};
  
}

void debugPrints() {
  Serial.print("\tjoystickLX: ");
  Serial.print(joystickLX);
  Serial.print("\tjoystickLY: ");
  Serial.print(joystickLY);
  Serial.print("\tjoystickLZ: ");
  Serial.print(joystickLZ);
  Serial.print("\tjostickRX: ");
  Serial.print(jostickRX);
  Serial.print("\tjostickRY: ");
  Serial.print(jostickRY);
  Serial.print("\tjostickRZ: ");
  Serial.print(jostickRZ);
  Serial.print("\tjoyBtnL: ");
  Serial.print(joyBtnL);
  Serial.print("\tjoyBtnR: ");
  Serial.print(joyBtnR);
  Serial.print("\ttoggleSwitch1: ");
  Serial.print(toggleSwitch1);
  Serial.print("\ttoggleSwitch2: ");
  Serial.print(toggleSwitch2);
  Serial.println();
}

// can you change this function so that the values are real "mixed together" - 
/* int calculateMotorSpeed(int Y, int X, int Z, char motorSide) {
    int mixer = 0;
    if (motorSide == 'L') {
        mixer = Y - (Z + X) / 2;  // Baseversion: Y - Z + X
    } else if (motorSide == 'R') {
        mixer = Y + (Z - X) / 2;  // Baseversion: Y + Z - X
    }
    return mixer;
}

int calculateMotorSpeed_OLD(int Y, int X, int Z, char motorSide) {
    int val;
    if (motorSide == 'L') {
        val = Y - abs(X)/2 - abs(Z)/2;  // Reduce left motor speed when turning right
    } else {
        val = Y + abs(X)/2 + abs(Z)/2;  // Reduce right motor speed when turning left
    }
    return val > 100 ? 100 : val;
} */

// Y stick does nothing for half the way
int calculateMotorSpeed(int Y, int X, int Z, char motorSide) {
  // Scaling factor for the turn influence
  // 1=ignore Y when steering
  // 0=ignore X when driving
  // 0.5=add half X to Y
  float turnScaleFactor = 0.5;  // COULD BE A POTI FROM THE REMOTE FROM 0.2-0.8 OR SO
  // Compute the preliminary motor speeds for differential steering
  int motorSpeedLeft = Y + X * turnScaleFactor;
  int motorSpeedRight = Y - X * turnScaleFactor;

  // somehow map the values - scale the smaller one if the bigger one is > maxSpeed

  // Return the appropriate motor speed based on the side
  if(motorSpeedLeft < 0 && motorSpeedRight < 0) {
    if (motorSide == 'R') {  // invert if backwards
      return constrain(motorSpeedLeft, -maxSpeed, maxSpeed);
    } else {
      return constrain(motorSpeedRight, -maxSpeed, maxSpeed);
    }

  } else {
    if (motorSide == 'L') {
      return constrain(motorSpeedLeft, -maxSpeed, maxSpeed);
    } else {
      return constrain(motorSpeedRight, -maxSpeed, maxSpeed);
    }
  }
}

void drive(int X, int Y, int Z) {
  /* Terack movement */
  // Values between 1000 and 2000
  X = clampMap(X, 1000,2000, -maxSpeed,maxSpeed);
  Y = clampMap(Y, 1000,2000, -maxSpeed,maxSpeed);
  Z = clampMap(Z, 1000,2000, maxSpeed,-maxSpeed);  // invert Z axis for some reason

  // static: XYZ == 500
  bool idle = isInDeadZone(X, 0, 1) && isInDeadZone(Y, 0, 1) && isInDeadZone(Z, 0, 1);
  // if not static, release clamps

  if(idle) {
    // Engange breaks
    digitalWrite(brakePinA, HIGH);
    digitalWrite(brakePinB, HIGH);
    analogWrite(pwmPinA, 0);  // 0-100%, not sure if necessary?
    analogWrite(pwmPinB, 0);  // 0-100%, not sure if necessary?
  } else {
    // Release breaks
    digitalWrite(brakePinA, LOW);
    digitalWrite(brakePinB, LOW);

    // Mix X Y Z together
    int motorL = calculateMotorSpeed(Y, X, Z, 'L');
    int motorR = calculateMotorSpeed(Y, X, Z, 'R');
    // Got values between -maxSpeed and maxSpeed (254)

    // Set direction
    digitalWrite(directionPinA, motorL < 0);  // LOW to reverse
    digitalWrite(directionPinB, motorR < 0);  // LOW to reverse

    Serial.print("\tmotorL: ");
    Serial.print(abs(motorL));
    Serial.print("\tdir_motorL: ");
    Serial.print(motorL < 0 ? "back" : "forward");
    Serial.print("\tmotorR: ");
    Serial.print(abs(motorR));
    Serial.print("\tdir_motorR: ");
    Serial.print(motorR < 0 ? "back" : "forward");
    Serial.println();

    // Z is inverted
    // values are over 100 when mixed together

    // Clamp?
    // motorL = abs(motorL) > maxSpeed ? maxSpeed : abs(motorL);
    // motorL = abs(motorR) > maxSpeed ? maxSpeed : abs(motorR);

    // Power to the motors
    analogWrite(pwmPinA, abs(motorL));  // abs makes out of -50 +50
    analogWrite(pwmPinB, abs(motorL));  // abs makes out of -50 +50
  }
}

bool isInDeadZone(int value, int idle, int deadzone) {
  bool isBelow = value < idle - deadzone/2;
  bool isAbove = value > idle + deadzone/2;
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
  /*if(abs(Z-1500) > abs(X-1500)) {
    X = Z < 1500 ? min(X, Z) : max(X, Z);
  }*/

  // Smooth out the signal
  float currentSmoothedX = exponentialMovingAverage(X, smoothedValueX, 0.1);
  float currentSmoothedY = exponentialMovingAverage(Y, smoothedValueY, 0.1);
  // float currentSmoothedZ = exponentialMovingAverage(Z, smoothedValueZ, 0.1);

  // Turning head X; ~120-170° range
  servoX.write(map(currentSmoothedX, 1000, 2000, 120, 170));

  // Bending head Y; ~170 (geradeausschauen) - 150° (runterschauen) range
  servoY.write(map(currentSmoothedY, 1000, 2000, 170, 150));
}

int clampMap(int value, int valueFrom, int valueTo, int from, int to) {
  if(value < valueFrom) value = valueFrom;
  if(value > valueTo) value = valueTo;
  return map(value, valueFrom, valueTo, from, to);
}


// from chatGPT:
/*
  The decode function does the reverse of the encode function.
  It takes an array of 9 integers (each representing the state of a group of 4 buttons)
  and fills an array of 36 boolean values representing the state of each button.
*/
void decodeButtonStates(int encodedStates[9], bool buttonStates[36]) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 4; j++) {
      buttonStates[i * 4 + j] = (encodedStates[i] & (1 << j)) != 0;
    }
  }
}