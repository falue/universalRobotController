/* 
  UNIVERSAL ROBOT CONTROLLER by FL
  with custom PCB
  based on james brutons remote controller
*/

// OPTIONS
bool trim = true;  // If true, poti 7,8,9,10 trim LX, LY, RX,RY

// USER INPUT -------------------------------------
int toggleSwitch1Pin = 31;  // Switch on top, left
int toggleSwitch2Pin = 33;  // Switch on top
int toggleSwitch3Pin = 32;  // Switch on top
int toggleSwitch4Pin = 35;  // Switch on top
int toggleSwitch5Pin = 34;  // Switch on top
int toggleSwitch6Pin = 36;  // Switch on top, right

int userBtn1Pin = 29;  // push button on top, left
int userBtn2Pin = 28;  // push button on top
int userBtn3Pin = 30;  // push button on top
int userBtn4Pin = 26;  // push button on top
int userBtn5Pin = 27;  // push button on top
int userBtn6Pin = 25;  // push button on top, right

int userBtn7Pin = 44;   // push button on side left, top
int userBtn8Pin = 45;   // push button on side left
int userBtn9Pin = 43;   // push button on side left
int userBtn10Pin = 41;  // push button on side left
int userBtn11Pin = 42;  // push button on side left
int userBtn12Pin = 40;  // push button on side left
int userBtn13Pin = 39;  // push button on side left
int userBtn14Pin = 38;  // push button on side left
int userBtn15Pin = 37;  // push button on side left, bottom

int userBtn18Pin = 12;  // PWM, push button on side right, top
int userBtn19Pin = 11;  // PWM, push button on side right, bottom

int joystickLXPin = A4;  // A3
int joystickLYPin = A3;  // A4
int joystickLZPin = A5;  // A5
int joyBtnLPin = 48;  // push button on top L joystick

int joystickRXPin = A1;  // A0
int joystickRYPin = A0;  // A1
int joystickRZPin = A2;  // A2
int joyBtnRPin = 49; // push button on top R joystick

int poti1Pin = A6;   // Poti on top, left
int poti2Pin = A7;   // Poti on top
int poti3Pin = A8;   // Poti on top
int poti4Pin = A9;   // Poti on top
int poti5Pin = A10;  // Poti on top
int poti6Pin = A11;  // Poti on top, right

int poti7Pin = A12;  // Poti bottom, left - maybe shifts joystickLX value directly?
int poti8Pin = A15;  // Poti bottom - maybe shifts joystickLY value directly?
int poti9Pin = A14;  // Poti bottom - maybe shifts joystickRX value directly?
int poti10Pin = A13; // Poti bottom, right - maybe shifts joystickRY value directly?

// SYSTEM -----------------------------------------
int sysBtn1Pin = 22;  // System button center, top
int sysBtn2Pin = 23;  // System button center
int sysBtn3Pin = 24;  // System button center, bottom

int transmitter1PpmPin = 9;   // PWM
int transmitter2PpmPin = 10;  // PWM

int systemLEDPin = 13;  // PWM, Same as built in
int tx1LEDPin = 7;      // PWM
int tx2LEDPin = 8;      // PWM
int systemLEDrPin = 6;  // PWM
int systemLEDgPin = 4;  // PWM
int systemLEDbPin = 5;  // PWM


// INITIAL VALUES
int toggleSwitch1 = 0;
int toggleSwitch2 = 0;
int toggleSwitch3 = 0;
int toggleSwitch4 = 0;
int toggleSwitch5 = 0;
int toggleSwitch6 = 0;
int userBtn1 = 0;
int userBtn2 = 0;
int userBtn3 = 0;
int userBtn4 = 0;
int userBtn5 = 0;
int userBtn6 = 0;
int userBtn7 = 0;
int userBtn8 = 0;
int userBtn9 = 0;
int userBtn10 = 0;
int userBtn11 = 0;
int userBtn12 = 0;
int userBtn13 = 0;
int userBtn14 = 0;
int userBtn15 = 0;
int userBtn18 = 0;
int userBtn19 = 0;
int joystickLX = 0;
int joystickLY = 0;
int joystickLZ = 0;
int joyBtnL = 0;
int joystickRX = 0;
int joystickRY = 0;
int joystickRZ = 0;
int joyBtnR = 0;
int poti1 = 0;
int poti2 = 0;
int poti3 = 0;
int poti4 = 0;
int poti5 = 0;
int poti6 = 0;
int poti7 = 0;
int poti8 = 0;
int poti9 = 0;
int poti10 = 0;
int sysBtn1 = 0;
int sysBtn2 = 0;
int sysBtn3 = 0;

// VAR VARS
bool DEBUG = true;  // Prints to console, makes stuff slow, kinda
int ledBrightness = 6;

void setup() {
  Serial.println("==============================");
  delay(1000);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Setup");
  Serial.println("==============================");
  
  pinMode(toggleSwitch1Pin, INPUT_PULLUP);
  pinMode(toggleSwitch2Pin, INPUT_PULLUP);
  pinMode(toggleSwitch3Pin, INPUT_PULLUP);
  pinMode(toggleSwitch4Pin, INPUT_PULLUP);
  pinMode(toggleSwitch5Pin, INPUT_PULLUP);
  pinMode(toggleSwitch6Pin, INPUT_PULLUP);
  pinMode(userBtn1Pin, INPUT_PULLUP);
  pinMode(userBtn2Pin, INPUT_PULLUP);
  pinMode(userBtn3Pin, INPUT_PULLUP);
  pinMode(userBtn4Pin, INPUT_PULLUP);
  pinMode(userBtn5Pin, INPUT_PULLUP);
  pinMode(userBtn6Pin, INPUT_PULLUP);
  pinMode(userBtn7Pin, INPUT_PULLUP);
  pinMode(userBtn8Pin, INPUT_PULLUP);
  pinMode(userBtn9Pin, INPUT_PULLUP);
  pinMode(userBtn10Pin, INPUT_PULLUP);
  pinMode(userBtn11Pin, INPUT_PULLUP);
  pinMode(userBtn12Pin, INPUT_PULLUP);
  pinMode(userBtn13Pin, INPUT_PULLUP);
  pinMode(userBtn14Pin, INPUT_PULLUP);
  pinMode(userBtn15Pin, INPUT_PULLUP);
  pinMode(userBtn18Pin, INPUT_PULLUP);
  pinMode(userBtn19Pin, INPUT_PULLUP);
  pinMode(joystickLXPin, INPUT);
  pinMode(joystickLYPin, INPUT);
  pinMode(joystickLZPin, INPUT);
  pinMode(joyBtnLPin, INPUT_PULLUP);
  pinMode(joystickRXPin, INPUT);
  pinMode(joystickRYPin, INPUT);
  pinMode(joystickRZPin, INPUT);
  pinMode(joyBtnRPin, INPUT_PULLUP);
  pinMode(poti1Pin, INPUT);
  pinMode(poti2Pin, INPUT);
  pinMode(poti3Pin, INPUT);
  pinMode(poti4Pin, INPUT);
  pinMode(poti5Pin, INPUT);
  pinMode(poti6Pin, INPUT);
  pinMode(poti7Pin, INPUT);
  pinMode(poti8Pin, INPUT);
  pinMode(poti9Pin, INPUT);
  pinMode(poti10Pin, INPUT);
  pinMode(sysBtn1Pin, INPUT_PULLUP);
  pinMode(sysBtn2Pin, INPUT_PULLUP);
  pinMode(sysBtn3Pin, INPUT_PULLUP);

  pinMode(transmitter1PpmPin, OUTPUT);
  pinMode(transmitter2PpmPin, OUTPUT);
  pinMode(systemLEDPin, OUTPUT);   // Maybe not; same as built in?
  pinMode(tx1LEDPin, OUTPUT);
  pinMode(tx2LEDPin, OUTPUT);
  pinMode(systemLEDrPin, OUTPUT);
  pinMode(systemLEDgPin, OUTPUT);
  pinMode(systemLEDbPin, OUTPUT);

  // LED tests
  analogWrite(tx1LEDPin, ledBrightness/2);
  delay(333);
  analogWrite(tx2LEDPin, ledBrightness/2);
  sysLED(ledBrightness,0,0);
  delay(333);
  sysLED(0,ledBrightness,0);
  delay(333);
  sysLED(0,0,ledBrightness);
  delay(333);
  sysLED(ledBrightness,ledBrightness,ledBrightness);
  delay(333);
  sysLED(0,0,0);
  delay(333);
  analogWrite(tx1LEDPin, 0);
  delay(333);
  analogWrite(tx2LEDPin, 0);
  blink(4,333);
  delay(333);
  sysLED(0,0,ledBrightness);
  
  Serial.println("Setup completed.");
  Serial.println("==============================");
}

void sysLED(int r, int g, int b) {
  analogWrite(systemLEDrPin, r);
  analogWrite(systemLEDgPin, g);
  analogWrite(systemLEDbPin, b);
}

void blink(int times, int duration) {
  for(int i = 0; i < times; i++) {
    sysLED(ledBrightness,ledBrightness,ledBrightness);
    delay(duration/3*2);
    sysLED(0,0,0);
    delay(duration/3);
  }
}
  

void loop() {
  readSignals();

  prepareSignals();

  if(DEBUG) {
    printSignals();
  }

  // First 12 values
  // int octave1[] = {joystickLX, joystickLY, joystickLZ, joystickRX, joystickRY, joystickRZ, joyBtnL, joyBtnR, toggleSwitch1, toggleSwitch2, toggleSwitch3, toggleSwitch4};
  // sendSignal(transmitter1PpmPin, octave1, 12);
  int octave1[] = {joystickLX, joystickLY, joystickLZ, joystickRX, joystickRY, joystickRZ, joyBtnL, joyBtnR, toggleSwitch1, toggleSwitch2};
  sendSignal(transmitter1PpmPin, octave1, 10);

  // Reduced channels
  ///// int octave1[] = {joystickLX, joystickLY, joystickLZ, joystickRX, joystickRY, joystickRZ, joyBtnL};
  ///// sendSignal(transmitter1PpmPin, octave1, 7);

  // Next 12 values
  int octave2[] = {};
  sendSignal(transmitter2PpmPin, octave2, 0);  // Maybe in parallel?

  catchSystemButtons();
}
         

void readSignals() {
  toggleSwitch1 = 1000 + !digitalRead(toggleSwitch1Pin)*1000; // Get 1000 for false, 2000 for true;
  toggleSwitch2 = 1000 + !digitalRead(toggleSwitch2Pin)*1000; // Get 1000 for false, 2000 for true;
  toggleSwitch3 = 1000 + !digitalRead(toggleSwitch3Pin)*1000; // Get 1000 for false, 2000 for true;
  toggleSwitch4 = 1000 + !digitalRead(toggleSwitch4Pin)*1000; // Get 1000 for false, 2000 for true;
  toggleSwitch5 = 1000 + !digitalRead(toggleSwitch5Pin)*1000; // Get 1000 for false, 2000 for true;
  toggleSwitch6 = 1000 + !digitalRead(toggleSwitch6Pin)*1000; // Get 1000 for false, 2000 for true;
  userBtn1 = 1000 + !digitalRead(userBtn1Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn2 = 1000 + !digitalRead(userBtn2Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn3 = 1000 + !digitalRead(userBtn3Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn4 = 1000 + !digitalRead(userBtn4Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn5 = 1000 + !digitalRead(userBtn5Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn6 = 1000 + !digitalRead(userBtn6Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn7 = 1000 + !digitalRead(userBtn7Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn8 = 1000 + !digitalRead(userBtn8Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn9 = 1000 + !digitalRead(userBtn9Pin)*1000;           // Get 1000 for false, 2000 for true;
  userBtn10 = 1000 + !digitalRead(userBtn10Pin)*1000;         // Get 1000 for false, 2000 for true;
  userBtn11 = 1000 + !digitalRead(userBtn11Pin)*1000;         // Get 1000 for false, 2000 for true;
  userBtn12 = 1000 + !digitalRead(userBtn12Pin)*1000;         // Get 1000 for false, 2000 for true;
  userBtn13 = 1000 + !digitalRead(userBtn13Pin)*1000;         // Get 1000 for false, 2000 for true;
  userBtn14 = 1000 + !digitalRead(userBtn14Pin)*1000;         // Get 1000 for false, 2000 for true;
  userBtn15 = 1000 + !digitalRead(userBtn15Pin)*1000;         // Get 1000 for false, 2000 for true;
  userBtn18 = 1000 + !digitalRead(userBtn18Pin)*1000;         // Get 1000 for false, 2000 for true;
  userBtn19 = 1000 + !digitalRead(userBtn19Pin)*1000;         // Get 1000 for false, 2000 for true;

  if(trim) {
    joystickLX =map(analogRead(joystickLXPin), 0,1023,1000,2000) + map(analogRead(poti7Pin), 0, 1024, -512, 512);
    joystickLY =map(analogRead(joystickLYPin), 0,1023,1000,2000) + map(analogRead(poti8Pin), 0, 1024, -512, 512);
  } else {
    joystickLX = map(analogRead(joystickLXPin), 0,1023,1000,2000);  
    joystickLY = map(analogRead(joystickLYPin), 0,1023,1000,2000);  
  }
  joystickLZ = map(analogRead(joystickLZPin), 0,1023,1000,2000);
  joyBtnL = 1000 + !digitalRead(joyBtnLPin)*1000; // Get 1000 for false, 2000 for true

  if(trim) {
    joystickRX =map(analogRead(joystickRXPin), 0,1023,1000,2000) + map(analogRead(poti9Pin), 0, 1024, -512, 512);
    joystickRY =map(analogRead(joystickRYPin), 0,1023,1000,2000) + map(analogRead(poti10Pin), 0, 1024, -512, 512);
  } else {
    joystickRX = map(analogRead(joystickRXPin), 0,1023,1000,2000);  
    joystickRY = map(analogRead(joystickRYPin), 0,1023,1000,2000);  
  }
  joystickRZ = map(analogRead(joystickRZPin), 0,1023,1000,2000);
  joyBtnR = 1000 + !digitalRead(joyBtnRPin)*1000; // Get 1000 for false, 2000 for true

  poti1 = map(analogRead(poti1Pin), 0,1023,2000,1000);
  poti2 = map(analogRead(poti2Pin), 0,1023,2000,1000);
  poti3 = map(analogRead(poti3Pin), 0,1023,2000,1000);
  poti4 = map(analogRead(poti4Pin), 0,1023,2000,1000);
  poti5 = map(analogRead(poti5Pin), 0,1023,2000,1000);
  poti6 = map(analogRead(poti6Pin), 0,1023,2000,1000);
  poti7 = map(analogRead(poti7Pin), 0,1023,1000,2000);  // If used for trimming, ignore
  poti8 = map(analogRead(poti8Pin), 0,1023,1000,2000);  // If used for trimming, ignore
  poti9 = map(analogRead(poti9Pin), 0,1023,1000,2000);  // If used for trimming, ignore
  poti10 = map(analogRead(poti10Pin), 0,1023,1000,2000);  // If used for trimming, ignore
  sysBtn1 = !digitalRead(sysBtn1Pin);
  sysBtn2 = !digitalRead(sysBtn2Pin);
  sysBtn3 = !digitalRead(sysBtn3Pin);
}

void prepareSignals() {
  // join var signals to one, map, ceil, floor, etc
  // + encodeButtonStates()
}

void encodeButtonStates(bool buttonStates[36], int encodedStates[9]) {
  /* 
    The encode function will take an array of 36 boolean values (true for pressed,
    false for not pressed) and return an array of 9 integers (each representing
    the state of a group of 4 buttons).
  */
  for (int i = 0; i < 9; i++) {
    encodedStates[i] = 0;
    for (int j = 0; j < 4; j++) {
      if (buttonStates[i * 4 + j]) {
        encodedStates[i] |= 1 << j;
      }
    }
  }
}

void printSignals() {
  Serial.print(joystickLX); Serial.print("\t");
  Serial.print(joystickLY); Serial.print("\t");
  Serial.print(joystickLZ); Serial.print("\t");
  Serial.print(joystickRX); Serial.print("\t");
  Serial.print(joystickRY); Serial.print("\t");
  Serial.print(joystickRZ); Serial.print("\t");
  Serial.print(joyBtnL > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  // ^^ This is the last print that "Serial Plotter" can handle

  Serial.print(joyBtnR > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch1 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch2 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch3 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch4 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch5 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch6 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn1 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn2 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn3 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn4 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn5 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn6 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn7 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn8 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn9 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn10 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn11 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn12 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn13 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn14 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn15 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn18 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn19 > 1500 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(poti1); Serial.print("\t");
  Serial.print(poti2); Serial.print("\t");
  Serial.print(poti3); Serial.print("\t");
  Serial.print(poti4); Serial.print("\t");
  Serial.print(poti5); Serial.print("\t");
  Serial.print(poti6); Serial.print("\t");
  Serial.print(poti7); Serial.print("\t");
  Serial.print(poti8); Serial.print("\t");
  Serial.print(poti9); Serial.print("\t");
  Serial.print(poti10); Serial.print("\t");
  
  Serial.print(sysBtn1 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(sysBtn2 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(sysBtn3 ? "🟢" : "⚫"); Serial.print("\t");

  Serial.println("");
}

void sendSignal(int transmitterPin, int* data, int dataSize) {
  // *** MAGIC ***
  // same function for both transmitters

  for(int i = 0; i < dataSize; i++) {
    digitalWrite(transmitterPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(transmitterPin, LOW);
    // gap for the remaining period:
    delayMicroseconds(data[i]-500);  // data[i] should be between 1000 and 2000
  }

  if(dataSize > 0) {
    if(transmitterPin == transmitter1PpmPin) analogWrite(tx1LEDPin, ledBrightness/2);
    if(transmitterPin == transmitter2PpmPin) analogWrite(tx2LEDPin, ledBrightness/2);
    // Send sync pulse
    digitalWrite(transmitterPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(transmitterPin, LOW);
    delayMicroseconds(10000);  // Longer gap to mark end of signal
  }
}

void catchSystemButtons() {
  /* 
    Check if any system buttons where pressed. wait until released. Do stuff.
  */

  if(sysBtn1) {
    analogWrite(systemLEDPin, ledBrightness);
    sysLED(ledBrightness,0,0);
    // wait for btn release
    while(!digitalRead(sysBtn1Pin)) {
      Serial.println("Trigger sysBtn1");
      delay(10);
      // interrupts RC signal transmission
    }
    analogWrite(systemLEDPin, 0);
    sysLED(0,0,ledBrightness);
    // do something
  }

  if(sysBtn2) {
    analogWrite(systemLEDPin, ledBrightness);
    sysLED(0,ledBrightness,0);
    // wait for btn release
    while(!digitalRead(sysBtn2Pin)) {
      Serial.println("Trigger sysBtn2");
      delay(10);
      // interrupts RC signal transmission
    }
    analogWrite(systemLEDPin, 0);
    sysLED(0,0,ledBrightness);
    // do something
  }

  if(sysBtn3) {
    analogWrite(systemLEDPin, ledBrightness);
    sysLED(ledBrightness,ledBrightness,ledBrightness);
    while(!digitalRead(sysBtn3Pin)) {
    // wait for btn release
      Serial.println("Trigger sysBtn3");
      delay(10);
      // interrupts RC signal transmission
    }
    analogWrite(systemLEDPin, 0);
    sysLED(0,0,ledBrightness);
    // do something
  }
}
