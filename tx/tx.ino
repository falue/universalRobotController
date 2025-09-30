/* 
  UNIVERSAL ROBOT CONTROLLER by FL
  with custom PCB
  based on james brutons remote controller
*/

// OPTIONS
bool trim = true;     // If true, poti 7,8,9,10 trim LX,LY,RX,RY. If false, those potis are not used.
int trimRange = 512;  // Plus minus half of that trims LX,LY,RX,RY
bool useSecondTransmitter = false;  // Send all btns and switches data over the second transmitter
String steeringLayout = "maxControl";
    // "conventional" => Use both joysticks with all three axis and their buttons, some switches, btns and potis (used for ProSenectute Robi), if useSecondTransmitter = true, use all buttons
    // "maxControl" => Use one joystick with one joyBtn, max use of buttons, switches and potis on one Transmitter module


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
bool toggleSwitch1 = false;
bool toggleSwitch2 = false;
bool toggleSwitch3 = false;
bool toggleSwitch4 = false;
bool toggleSwitch5 = false;
bool toggleSwitch6 = false;
bool userBtn1 = false;
bool userBtn2 = false;
bool userBtn3 = false;
bool userBtn4 = false;
bool userBtn5 = false;
bool userBtn6 = false;
bool userBtn7 = false;
bool userBtn8 = false;
bool userBtn9 = false;
bool userBtn10 = false;
bool userBtn11 = false;
bool userBtn12 = false;
bool userBtn13 = false;
bool userBtn14 = false;
bool userBtn15 = false;
bool userBtn18 = false;
bool userBtn19 = false;
int joystickLX = 0;
int joystickLY = 0;
int joystickLZ = 0;
bool joyBtnL = false;
int joystickRX = 0;
int joystickRY = 0;
int joystickRZ = 0;
bool joyBtnR = false;
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
bool sysBtn1 = false;
bool sysBtn2 = false;
bool sysBtn3 = false;

// VAR VARS
bool DEBUG = true;  // Prints to console, makes stuff slow, kinda
int ledBrightness = 6;

void setup() {
  delay(1000);
  Serial.println("==============================");
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

  // LED tests - jump if pressing sysbtn-3
  if(digitalRead(sysBtn3Pin)) {
    Serial.println("LED tests..");
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
  } else {
    Serial.println("LED tests - jumped");
    sysLED(0,0,ledBrightness);
  }
  
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
  readInputs();

  if(DEBUG) {
    printSignals();
  }

  if(steeringLayout == "conventional") {
    // Use both joysticks with all three axis and their buttons, some switches, btns and potis (used for ProSenectute Robi)
    // Values for first transmitter box - these are the most important ones
    // TODO: Transmitter & receiver should work with 12 channels but cannot get it to transmit (or receive?) with more than 10
    int encodedButtons0 = encodeButtons(toggleSwitch1,toggleSwitch2,toggleSwitch3,toggleSwitch4);
    int encodedButtons1 = encodeButtons(joyBtnL,joyBtnR,userBtn1,userBtn2);
    int octave1[] = {joystickLX, joystickLY, joystickLZ, joystickRX, joystickRY, joystickRZ, encodedButtons0, encodedButtons1, poti1, poti2};
    sendSignal(transmitter1PpmPin, octave1, 10);

    // Values for second transmitter box
    // One full channel and 3 switches still fit in the signal
    if(useSecondTransmitter) {
      int encodedButtons2 = encodeButtons(toggleSwitch5, toggleSwitch6, userBtn3, userBtn4);
      int encodedButtons3 = encodeButtons(userBtn5, userBtn6, userBtn7, userBtn8);
      int encodedButtons4 = encodeButtons(userBtn9, userBtn10, userBtn11, userBtn12);
      int encodedButtons5 = encodeButtons(userBtn13, userBtn14, userBtn15, userBtn18);
      int encodedButtons6 = encodeButtons(userBtn19, sysBtn1, sysBtn2, sysBtn3);  // sysBtns make no sense to send but they fit in here, and who knows?
      int octave2[] = {poti3, poti4, poti5, poti6, encodedButtons2, encodedButtons3, encodedButtons4, encodedButtons5, encodedButtons6, 1500};
      sendSignal(transmitter2PpmPin, octave2, 10);
    }
  } else if(steeringLayout == "maxControl") {
    // Use one joystick with one joyBtn, max use of buttons, switches and potis
    int encodedButtons0 = encodeButtons(toggleSwitch1,toggleSwitch2,toggleSwitch3,toggleSwitch4);
    int encodedButtons1 = encodeButtons(joyBtnL,userBtn1,userBtn2,userBtn3);
    int encodedButtons2 = encodeButtons(userBtn4,userBtn5,userBtn6,userBtn7);
    int octave1[] = {joystickLX, joystickLY, joystickLZ, encodedButtons0, encodedButtons1, encodedButtons2, poti1, poti2, poti3, poti4 };
    sendSignal(transmitter1PpmPin, octave1, 10); 
  }

  catchSystemButtons();
}

int encodeButtons(bool state1, bool state2, bool state3, bool state4) {
  // Create a binary number from the button states
  int encodedValue = (state1 << 0) | (state2 << 1) | (state3 << 2) | (state4 << 3);
  // Scale the binary value from 0-15 to 1000-2000
  return map(encodedValue, 0, 15, 1000, 2000);
}

void readInputs() {
  toggleSwitch1 = !digitalRead(toggleSwitch1Pin);
  toggleSwitch2 = !digitalRead(toggleSwitch2Pin);
  toggleSwitch3 = !digitalRead(toggleSwitch3Pin);
  toggleSwitch4 = !digitalRead(toggleSwitch4Pin);
  toggleSwitch5 = !digitalRead(toggleSwitch5Pin);
  toggleSwitch6 = !digitalRead(toggleSwitch6Pin);
  userBtn1 = !digitalRead(userBtn1Pin);
  userBtn2 = !digitalRead(userBtn2Pin);
  userBtn3 = !digitalRead(userBtn3Pin);
  userBtn4 = !digitalRead(userBtn4Pin);
  userBtn5 = !digitalRead(userBtn5Pin);
  userBtn6 = !digitalRead(userBtn6Pin);
  userBtn7 = !digitalRead(userBtn7Pin);
  userBtn8 = !digitalRead(userBtn8Pin);
  userBtn9 = !digitalRead(userBtn9Pin);
  userBtn10 = !digitalRead(userBtn10Pin);
  userBtn11 = !digitalRead(userBtn11Pin);
  userBtn12 = !digitalRead(userBtn12Pin);
  userBtn13 = !digitalRead(userBtn13Pin);
  userBtn14 = !digitalRead(userBtn14Pin);
  userBtn15 = !digitalRead(userBtn15Pin);
  userBtn18 = !digitalRead(userBtn18Pin);
  userBtn19 = !digitalRead(userBtn19Pin);

  if(trim) {
    joystickLX =map(analogRead(joystickLXPin), 0,1023,1000,2000) + map(analogRead(poti7Pin), 0, 1024, trimRange/2*-1, trimRange/2);
    joystickLY =map(analogRead(joystickLYPin), 0,1023,1000,2000) + map(analogRead(poti8Pin), 0, 1024, trimRange/2*-1, trimRange/2);
  } else {
    joystickLX = map(analogRead(joystickLXPin), 0,1023,1000,2000);  
    joystickLY = map(analogRead(joystickLYPin), 0,1023,1000,2000);  
  }
  joystickLZ = map(analogRead(joystickLZPin), 0,1023,1000,2000);
  joyBtnL = !digitalRead(joyBtnLPin);

  if(trim) {
    joystickRX =map(analogRead(joystickRXPin), 0,1023,1000,2000) + map(analogRead(poti9Pin), 0, 1024, trimRange/2*-1, trimRange/2);
    joystickRY =map(analogRead(joystickRYPin), 0,1023,1000,2000) + map(analogRead(poti10Pin), 0, 1024, trimRange/2*-1, trimRange/2);
  } else {
    joystickRX = map(analogRead(joystickRXPin), 0,1023,1000,2000);  
    joystickRY = map(analogRead(joystickRYPin), 0,1023,1000,2000);  
  }
  joystickRZ = map(analogRead(joystickRZPin), 0,1023,1000,2000);
  joyBtnR = !digitalRead(joyBtnRPin);

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

  // For use on the remote itself
  sysBtn1 = !digitalRead(sysBtn1Pin);
  sysBtn2 = !digitalRead(sysBtn2Pin);
  sysBtn3 = !digitalRead(sysBtn3Pin);
}

void printSignals() {
  Serial.print(joystickLX); Serial.print("\t");
  Serial.print(joystickLY); Serial.print("\t");
  Serial.print(joystickLZ); Serial.print("\t");
  Serial.print(joystickRX); Serial.print("\t");
  Serial.print(joystickRY); Serial.print("\t");
  Serial.print(joystickRZ); Serial.print("\t");
  Serial.print(joyBtnL ? "🟢" : "⚫"); Serial.print("\t");
  // ^^ This is the last print that "Serial Plotter" can handle

  Serial.print(joyBtnR ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch1 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch2 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch3 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch4 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch5 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(toggleSwitch6 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn1 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn2 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn3 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn4 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn5 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn6 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn7 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn8 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn9 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn10 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn11 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn12 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn13 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn14 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn15 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn18 ? "🟢" : "⚫"); Serial.print("\t");
  Serial.print(userBtn19 ? "🟢" : "⚫"); Serial.print("\t");
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
  // Same function for both transmitters
  int gap = 500;
  int longGap = 1000;  // 10'000 according to james bruton, but its very slow and 1000 works too?!

  for(int i = 0; i < dataSize; i++) {
    digitalWrite(transmitterPin, HIGH);
    delayMicroseconds(gap);
    digitalWrite(transmitterPin, LOW);
    // gap for the remaining period:
    delayMicroseconds(data[i]-gap);  // data[i] should be between 1000 and 2000
  }

  if(dataSize > 0) {
    if(transmitterPin == transmitter1PpmPin) analogWrite(tx1LEDPin, ledBrightness/2);
    if(transmitterPin == transmitter2PpmPin) analogWrite(tx2LEDPin, ledBrightness/2);
    // Send sync pulse
    digitalWrite(transmitterPin, HIGH);
    delayMicroseconds(gap);
    digitalWrite(transmitterPin, LOW);
    delayMicroseconds(longGap);  // Longer gap to mark end of signal
  }
}

void catchSystemButtons() {
  /* 
    Check if any system buttons where pressed. wait until released. Do stuff.
  */

  if(sysBtn1) {
    // Block all inputs / outputs
    analogWrite(systemLEDPin, ledBrightness);
    sysLED(ledBrightness,0,0);
    // wait for btn release
    while(!digitalRead(sysBtn1Pin)) {
      Serial.println("Trigger sysBtn1");
      delay(10);
      // interrupts RC signal transmission
    }

    // Wait for pressing btn again
    while(digitalRead(sysBtn1Pin)) {
      Serial.println("Halting all signals - press sysBtn1 again");
      // Blink led every ~1s
      if(millis() % 1000 >= 500) {
        sysLED(255,0,0);
      } else {
        sysLED(0,0,0);
      }
      delay(10);
      // interrupts RC signal transmission
    }
    sysLED(ledBrightness,ledBrightness,ledBrightness);

    while(!digitalRead(sysBtn1Pin)) {
      Serial.println("Wait for release sysBtn1");
      delay(10);
      // interrupts RC signal transmission
    }
    analogWrite(systemLEDPin, 0);
    sysLED(0,0,ledBrightness);
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
