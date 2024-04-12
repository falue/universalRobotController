/* 
  UNIVERSAL ROBOT CONTROLLER by FL
  with custom PCB
  based on james brutons remote controller
*/

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

int jostickLXPin = A3;
int jostickLYPin = A4;
int jostickLZPin = A5;
int joyBtnLPin = 48;  // push button on top L joystick

int jostickRXPin = A0;
int jostickRYPin = A1;
int jostickRZPin = A2;
int joyBtnRPin = 46; // push button on top R joystick  // was 49, but is hsorted somehow! solder wire;

int poti1Pin = A6;   // Poti on top, left
int poti2Pin = A7;   // Poti on top
int poti3Pin = A8;   // Poti on top
int poti4Pin = A9;   // Poti on top
int poti5Pin = A10;  // Poti on top
int poti6Pin = A11;  // Poti on top, right

int poti7Pin = A12;  // Poti bottom, left - maybe shifts jostickLX value directly?
int poti8Pin = A15;  // Poti bottom - maybe shifts jostickLY value directly?
int poti9Pin = A14;  // Poti bottom - maybe shifts jostickRX value directly?
int poti10Pin = A13; // Poti bottom, right - maybe shifts jostickRY value directly?

// SYSTEM -----------------------------------------
int sysBtn1Pin = 22;  // System button center, top
int sysBtn2Pin = 23;  // System button center
int sysBtn3Pin = 24;  // System button center, bottom

int transmitter1PpmPin = 9;   // PWM
int transmitter2PpmPin = 10;  // PWM

int systemLEDPin = 13;  // PWM, Same as built in
int tx1LEDPin = 7;      // PWM
int tx2LEDPin = 8;      // PWM
int systemLEDrPin = 4;  // PWM
int systemLEDgPin = 5;  // PWM
int systemLEDbPin = 6;  // PWM


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
int jostickLX = 0;
int jostickLY = 0;
int jostickLZ = 0;
int joyBtnL = 0;
int jostickRX = 0;
int jostickRY = 0;
int jostickRZ = 0;
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
bool DEBUG = true;  // Prints to console

void setup() {
  Serial.println("==============================");
  delay(1000);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("In setup");
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
  pinMode(jostickLXPin, INPUT);
  pinMode(jostickLYPin, INPUT);
  pinMode(jostickLZPin, INPUT);
  pinMode(joyBtnLPin, INPUT_PULLUP);
  pinMode(jostickRXPin, INPUT);
  pinMode(jostickRYPin, INPUT);
  pinMode(jostickRZPin, INPUT);
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
  analogWrite(tx1LEDPin, 255);
  analogWrite(tx2LEDPin, 255);
  sysLED(255,0,0);
  delay(333);
  sysLED(0,255,0);
  delay(333);
  sysLED(0,0,255);
  delay(333);
  sysLED(255,255,255);
  delay(333);
  sysLED(0,0,0);
  delay(333);
  analogWrite(tx1LEDPin, 0);
  analogWrite(tx2LEDPin, 0);
  blink(4,333);
  sysLED(0,0,255);


  /* pinMode(38, INPUT_PULLUP);    // digital switches
  pinMode(40, INPUT_PULLUP);
  pinMode(42, INPUT_PULLUP);
  pinMode(44, INPUT_PULLUP);
  pinMode(46, INPUT_PULLUP);
  pinMode(48, INPUT_PULLUP);
  pinMode(50, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);
  
  pinMode(9, OUTPUT);       // PPM output pin - first 10
  pinMode(10, OUTPUT);      // PPM output pin - second 10 */
  
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
    sysLED(255,255,255);
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
  int octave1[] = {jostickLX, jostickLY, jostickLZ, jostickRX, jostickRY, jostickRZ, joyBtnL, joyBtnR, toggleSwitch1, toggleSwitch2, toggleSwitch3, toggleSwitch4};
  sendSignal(transmitter1PpmPin, octave1, 12);

  // Next 12 values
  int octave2[] = {};
  sendSignal(transmitter2PpmPin, octave2, 0);  // Maybe in parallel?

  catchSystemButtons();

  /* ch1 = analogRead(A0);          // read analog sticks
  ch1 = map(ch1, 0,1023,1000,2000);
  ch2 = analogRead(A1);
  ch2 = map(ch2, 0,1023,1000,2000);
  ch3 = analogRead(A2);
  ch3 = map(ch3, 0,1023,1000,2000);
  ch4 = analogRead(A3);
  ch4 = map(ch4, 0,1023,1000,2000);
  ch5 = analogRead(A4);
  ch5 = map(ch5, 0,1023,1000,2000);
  ch6 = analogRead(A5);
  ch6 = map(ch6, 0,1023,1000,2000);
  ch7 = analogRead(A6);
  ch7 = map(ch7, 0,1023,1000,2000);
  ch8 = analogRead(A7);
  ch8 = map(ch8, 0,1023,1000,2000);
  ch9 = analogRead(A8);
  ch9 = map(ch9, 0,1023,1000,2000);
  ch10 = analogRead(A9);
  ch10 = map(ch10, 0,1023,1000,2000);
  ch11 = analogRead(A10);
  ch11 = map(ch11, 0,1023,1000,2000);
  ch12 = analogRead(A11);
  ch12 = map(ch12, 0,1023,1000,2000);

  sw1 = digitalRead(38);
  sw2 = digitalRead(40);
  sw3 = digitalRead(44);
  sw4 = digitalRead(42);
  sw5 = digitalRead(46);
  sw6 = digitalRead(50);
  sw7 = digitalRead(48);
  sw8 = digitalRead(52);

   
  // sw channel 1   
  if (sw1 == 1 && sw2 == 1) {
    swCombo1 = 1100;
  }
  else if (sw1 == 0 && sw2 == 1) {
    swCombo1 = 1400;
  }
  else if (sw1 == 1 && sw2 == 0) {
    swCombo1 = 1700;
  }
  else if (sw1 == 0 && sw2 == 0) {
    swCombo1 = 2000;
  }
  
  // sw channel 2
  if (sw3 == 1 && sw4 == 1) {
    swCombo2 = 1100;
  }
  else if (sw3 == 0 && sw4 == 1) {
    swCombo2 = 1400;
  }
  else if (sw3 == 1 && sw4 == 0) {
    swCombo2 = 1700;
  }
  else if (sw3 == 0 && sw4 == 0) {
    swCombo2 = 2000;
  }
  
  // sw channel 3
  if (sw5 == 1 && sw6 == 1) {
    swCombo3 = 1100;
  }
  else if (sw5 == 0 && sw6 == 1) {
    swCombo3 = 1400;
  }
  else if (sw5 == 1 && sw6 == 0) {
    swCombo3 = 1700;
  }
  else if (sw5 == 0 && sw6 == 0) {
    swCombo3 = 2000;
  }
  
  // sw channel 4
  if (sw7 == 1 && sw8 == 1) {
    swCombo4 = 1100;
  }
  else if (sw7 == 0 && sw8 == 1) {
    swCombo4 = 1400;
  }
  else if (sw7 == 1 && sw8 == 0) {
    swCombo4 = 1700;
  }
  else if (sw7 == 0 && sw8 == 0) {
    swCombo4 = 2000;
  }


  // first octave

  digitalWrite(9, HIGH);
  delayMicroseconds(500);         // ch1
  digitalWrite(9, LOW);
  delayMicroseconds(ch1-500);     // gap for the remaining period
  
  digitalWrite(9, HIGH);              
  delayMicroseconds(500);         // ch2
  digitalWrite(9, LOW);     
  delayMicroseconds(ch2-500);   
  
  digitalWrite(9, HIGH);        
  delayMicroseconds(500);         // ch3
  digitalWrite(9, LOW);      
  delayMicroseconds(ch5-500);   

  digitalWrite(9, HIGH);
  delayMicroseconds(500);         // ch4 
  digitalWrite(9, LOW);      
  delayMicroseconds(ch6-500);   

  digitalWrite(9, HIGH);        
  delayMicroseconds(500);         // ch5
  digitalWrite(9, LOW);        
  delayMicroseconds(ch9-500);   

  digitalWrite(9, HIGH);          // ch6 
  delayMicroseconds(500);
  digitalWrite(9, LOW);      
  delayMicroseconds(ch10-500);

  digitalWrite(9, HIGH);          // ch7 
  delayMicroseconds(500);
  digitalWrite(9, LOW);      
  delayMicroseconds(swCombo1-500);

  digitalWrite(9, HIGH);          // ch8 
  delayMicroseconds(500);
  digitalWrite(9, LOW);      
  delayMicroseconds(swCombo2-500);

  digitalWrite(9, HIGH);          // ch9 
  delayMicroseconds(500);
  digitalWrite(9, LOW);      
  delayMicroseconds(swCombo3-500);

  digitalWrite(9, HIGH);          // ch10 
  delayMicroseconds(500);
  digitalWrite(9, LOW);      
  delayMicroseconds(swCombo4-500);     

  digitalWrite(9, HIGH);          // sync pulse
  delayMicroseconds(500);
  digitalWrite(9, LOW);
  delayMicroseconds(10000);        // longer gap


  // second octave

  digitalWrite(10, HIGH);
  delayMicroseconds(500);           // ch1
  digitalWrite(10, LOW);
  delayMicroseconds(ch3-500);       // gap for the remaining period
  
  digitalWrite(10, HIGH);        
  delayMicroseconds(500);           // ch2
  digitalWrite(10, LOW);     
  delayMicroseconds(ch4-500);   
  
  digitalWrite(10, HIGH);           
  delayMicroseconds(500);           // ch3
  digitalWrite(10, LOW);      
  delayMicroseconds(ch7-500);   

  digitalWrite(10, HIGH);
  delayMicroseconds(500);           // ch3
  digitalWrite(10, LOW);      
  delayMicroseconds(ch8-500);   

  digitalWrite(10, HIGH);        
  delayMicroseconds(500);           // ch4
  digitalWrite(10, LOW);        
  delayMicroseconds(ch11-500);   

  digitalWrite(10, HIGH);           // ch6 
  delayMicroseconds(500);
  digitalWrite(10, LOW);      
  delayMicroseconds(ch12-500);

  digitalWrite(10, HIGH);           // ch7 - spare 
  delayMicroseconds(500);
  digitalWrite(10, LOW);      
  delayMicroseconds(1500-500);

  digitalWrite(10, HIGH);          // ch8 - spare
  delayMicroseconds(500);
  digitalWrite(10, LOW);      
  delayMicroseconds(1500-500);

  digitalWrite(10, HIGH);          // ch9 - spare 
  delayMicroseconds(500);
  digitalWrite(10, LOW);      
  delayMicroseconds(1500-500);

  digitalWrite(10, HIGH);          // ch10 - spare
  delayMicroseconds(500);
  digitalWrite(10, LOW);      
  delayMicroseconds(1500-500);   

  digitalWrite(10, HIGH);          // sync pulse
  delayMicroseconds(500);
  digitalWrite(10, LOW);
  delayMicroseconds(10000);        // longer gap
 */
}
         

void readSignals() {
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
  // map(ch8, 0,1023,1000,2000);
  jostickLX = map(analogRead(jostickLXPin), 0,1023,1000,2000);  // TRIM? analogRead(jostickLXPin) + map(analogRead(poti7Pin), 0, 1024, -512, 512)
  jostickLY = map(analogRead(jostickLYPin), 0,1023,1000,2000);  // TRIM? analogRead(jostickLYPin) + map(analogRead(poti8Pin), 0, 1024, -512, 512)
  jostickLZ = map(analogRead(jostickLZPin), 0,1023,1000,2000);
  joyBtnL = !digitalRead(joyBtnLPin);
  jostickRX = map(analogRead(jostickRXPin), 0,1023,1000,2000);  // TRIM? analogRead(jostickRXPin) + map(analogRead(poti9Pin), 0, 1024, -512, 512)
  jostickRY = map(analogRead(jostickRYPin), 0,1023,1000,2000);  // TRIM? analogRead(jostickRYPin) + map(analogRead(poti10Pin), 0, 1024, -512, 512)
  jostickRZ = map(analogRead(jostickRZPin), 0,1023,1000,2000);
  joyBtnR = !digitalRead(joyBtnRPin);
  poti1 = map(analogRead(poti1Pin), 0,1023,1000,2000);
  poti2 = map(analogRead(poti2Pin), 0,1023,1000,2000);
  poti3 = map(analogRead(poti3Pin), 0,1023,1000,2000);
  poti4 = map(analogRead(poti4Pin), 0,1023,1000,2000);
  poti5 = map(analogRead(poti5Pin), 0,1023,1000,2000);
  poti6 = map(analogRead(poti6Pin), 0,1023,1000,2000);
  poti7 = map(analogRead(poti7Pin), 0,1023,1000,2000);  // If used for trimming, ignore
  poti8 = map(analogRead(poti8Pin), 0,1023,1000,2000);  // If used for trimming, ignore
  poti9 = map(analogRead(poti9Pin), 0,1023,1000,2000);  // If used for trimming, ignore
  poti10 = map(analogRead(poti10Pin), 0,1023,1000,2000);  // If used for trimming, ignore
  sysBtn1 = !digitalRead(sysBtn1Pin);
  sysBtn2 = !digitalRead(sysBtn2Pin);
  sysBtn3 = !digitalRead(sysBtn3Pin);
}

void prepareSignals() {
  // join var signals to one, map, ceil, floor, trim potis with other potis, etc
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
  Serial.print(jostickLX); Serial.print("\t");
  Serial.print(jostickLY); Serial.print("\t");
  Serial.print(jostickLZ); Serial.print("\t");
  Serial.print(jostickRX); Serial.print("\t");
  Serial.print(jostickRY); Serial.print("\t");
  Serial.print(jostickRZ); Serial.print("\t");
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
  // same function for both transmitters

  for(int i = 0; i < dataSize; i++) {
    digitalWrite(transmitterPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(transmitterPin, LOW);
    // gap for the remaining period:
    delayMicroseconds(data[i]-500);  // data[i] should be between 1000 and 2000
  }

  // Send sync pulse
  digitalWrite(transmitterPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(transmitterPin, LOW);
  delayMicroseconds(10000);  // Longer gap to mark end of signal
}

void catchSystemButtons() {
  /* 
  Check if any system buttons where pressed. wait until released. Do stuff.

  sysBtn1
  sysBtn2
  sysBtn3

  if(sysBtn1) {
    Serial.println("Trigger sysBtn1");
    analogWrite(tx1LEDPin, 255);
    while(sysBtn1) {
      delay(10);  // wait for btn release
      // interrupts RC signal (?)
    }
    analogWrite(tx1LEDPin, 0);
    // do something
  }

  */

}
