/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservoX;  // create servo object to control a servo
Servo myservoY;  // create servo object to control a servo
// twelve servo objects can be created on most boards


int minX = 1700;  // links min X
int maxX = 2300;  // rechts max X
int minY = 1950;  // runter min Y
int maxY = 2300;  // hoch max Y
int speed = 5;
int pos = minX;    // variable to store the servo position

void setup() {
  myservoX.attach(2);  // attaches the servo on pin 9 to the servo object
  myservoY.attach(10);  // attaches the servo on pin 9 to the servo object
  Serial.begin(115200);   // remove comment from this line if you change the Serial port in the next line
  pos = myservoX.readMicroseconds();
}

void loop() {
  for (pos = minX; pos <= maxX; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservoX.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(speed);                       // Wait Xms for the servo to reach the position
  }
  delay(2500);                       // Wait Xms for the servo to reach the position

  for (pos = minY; pos <= maxY; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservoY.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(speed);                       // Wait Xms for the servo to reach the position
  }
  delay(2500);  

  for (pos = maxX; pos >= minX; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservoX.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(speed);                       // Wait Xms for the servo to reach the position
  }
  delay(2500);                       // Wait Xms for the servo to reach the position

  for (pos = maxY; pos >= minY; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservoY.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'
    Serial.println(pos);
    delay(speed);                       // Wait Xms for the servo to reach the position
  }
  delay(2500);                       // Wait Xms for the servo to reach the position
}

