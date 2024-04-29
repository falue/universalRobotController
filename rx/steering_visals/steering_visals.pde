import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
int LX = 1500, LY = 1500, LZ = 1500;
int motorL = 0, motorR = 0;
String dir_motorL = "forward", dir_motorR = "forward";

Boolean use_Serial = true;

float handleX, handleY; // Position of the joystick handle
float handleRadius = 50; // Radius of the draggable handle
boolean dragging = false; // Is the handle being dragged?

int heightWindow = 666;
int diameter = 100;
int radius = diameter / 2;
int circleX = radius + 20;
int circleY = heightWindow - radius - 20;

void setup() {
  size(1000, 666); // Set the window size to 1000x666 pixels
  smooth(); // Smooths out the drawing
  println("Available serial ports:");
  // Print all the available serial ports
  printArray(Serial.list());
  
  String portName = Serial.list()[8]; // Change this to your Arduino port
  myPort = new Serial(this, portName, 115200);
  myPort.bufferUntil('\n');          // Buffer until a newline character
  
  handleX = circleX; // Initially place handle at the center of the base
  handleY = circleY;
}

void draw() {
  background(33); // Set background to black
  fill(255); // Set text color to white
  textSize(16);
  textAlign(LEFT);
  // Display the serial data at position (10, 20)
  text("LX: " + LX + ", LY: " + LY + ", LZ: " + LZ + ", Motor L: " + motorL + ", Motor R: " + motorR, 10, 20);
  
  joystick(LX, LY, LZ); // Mid values for LX and LY
  
  tracks(motorL, motorR); // Mid-range values for motorL and motorR
}
/*
void mousePressed() {
  float d = dist(mouseX, mouseY, handleX, handleY);
  if (d < handleRadius) {
    dragging = true;
  }
}

void mouseReleased() {
  dragging = false;
}

void mouseDragged() {
  if (dragging) {
    LX = int(map(mouseX, 0,1200, 1000,2000));
    motorL = int(map(mouseX, 0,1200, 0,100));
    LY = int(map(mouseY, 0,666, 1000,2000));
  }
}*/


// Function to draw the joystick representation
void joystick(int LX, int LY, int LZ) {
  // Draw the circle at bottom left
  fill(100); // Light gray fill
  stroke(0); // Black outline
  ellipse(circleX, circleY, diameter, diameter);
  
  stroke(255); // green outline
  strokeWeight(4); // Thick line
  // Map LZ to an angle between -PI/4 to PI/4
  float rotationAngle = map(LZ, 1000, 2000, -PI/2 - PI/4, -PI/2 + PI/4);
  float startAngle = -PI/4 + rotationAngle;
  float endAngle = PI/4 + rotationAngle;
  arc(circleX, circleY, 100, 100, startAngle, endAngle); // Draw an arc from -45 degrees to 45 degrees

  // Map LX and LY to screen coordinates
  float posX = map(LX, 1000, 2000, circleX - radius, circleX + radius);
  float posY = map(LY, 1000, 2000, circleY + radius, circleY - radius);

  // Knob
  fill(255,100,20);
  stroke(133,133,133); // red outline
  strokeWeight(2); // Thick line
  ellipse(circleX, circleY, 16, 16);
  
  // Draw a line from center of the circle to the calculated position
  strokeWeight(6); // Thick line
  stroke(255,0,0); // red outline
  line(circleX, circleY, posX, posY);
  
  // Knob
  fill(255,100,20);
  strokeWeight(1); // Thick line
  ellipse(posX, posY, 20, 20);
}

void tracks(int motorL, int motorR) {
  int trackWidth = 40; // Width of each track
  int trackHeight = 100; // Height of each track
  int margin = 20; // Margin from the edges of the window

  // Coordinates for the bottom-right placement of the tracks
  int trackX1 = width - margin - trackWidth * 2 - 100; // X position for the first track
  int trackX2 = width - margin - trackWidth; // X position for the second track, with some space between
  

  // Map motor values from 1000-2000 to 0-trackHeight for the fill level
  int fillHeightL = int(map(motorL, 0, 100, 0, trackHeight));
  int fillHeightR = int(map(motorR, 0, 100, 0, trackHeight));

  // Draw the inner rectangles (filled based on motor values)
  noStroke();
  if(dir_motorL.equals("forward")) {
    fill(0,0,255);
    rect(trackX1, height - margin - fillHeightL, trackWidth, fillHeightL);
  } else {
    fill(255,0,0);
    rect(trackX1, height - margin - trackHeight, trackWidth, fillHeightL);
  }
  if(dir_motorR.equals("forward")) {
    fill(0,0,255);
    rect(trackX2, height - margin - fillHeightR, trackWidth, fillHeightR);  //////fillHeightR
  } else {
    fill(255,0,0);
    rect(trackX2, height - margin - trackHeight, trackWidth, fillHeightR);  //////fillHeightR
  }
  
  // Robi
  strokeWeight(1); // Thick line
  stroke(133,133,133); // red outline
  noFill(); // No fill for the outer rectangles
  rect(trackX1+trackWidth+10, height - margin - trackHeight+20, 80, 80);
  
  // Draw the outer rectangles (tracks)
  strokeWeight(2); // Thick line
  stroke(255,255,0); // red outline
  noFill(); // No fill for the outer rectangles
  rect(trackX1, height - margin - trackHeight, trackWidth, trackHeight);
  rect(trackX2, height - margin - trackHeight, trackWidth, trackHeight);
  
  fill(255,255,255);
  textAlign(CENTER);
  textSize(28);
  text(motorL, trackX1+trackWidth/2, height - margin - trackHeight-35);
  text(motorR, trackX2+trackWidth/2, height - margin - trackHeight-35);
  
  textSize(18);
  text(dir_motorL, trackX1+trackWidth/2, height - margin - trackHeight-10);
  text(dir_motorR, trackX2+trackWidth/2, height - margin - trackHeight-10);
}


void serialEvent(Serial myPort) {
  if(use_Serial) {
    val = myPort.readStringUntil('\n');
    // print(splitTokens(val, ": ").length);
    // println(val);
    if (val != null) {
      val = trim(val);  // Trim whitespace
      // println(val);
      
      // Parse the incoming data
      String[] data = splitTokens(val, ": "); // Split the data by tabs and colons
      if(data != null) {
        if (data.length == 15) { // Check if all elements are present
          // LX: 1500  LY: 1794  LZ: 1500  steering: ▲  motorL: 58  dir_motorL: ▲  motorR: 58  dir_motorR: ▲
          // motorL: 17  dir_motorL: forward  motorR: 17  dir_motorR: back  joystickLX: 1586  joystickLY: 1454  joystickLZ: 1692  jostickRX: 1485  jostickRY: 1509  jostickRZ: 1513  joyBtnL: 1019  joyBtnR: 1019  motorSwitch: 1  servoSwitch: 0

          LX = int(data[5].split("\t")[0]);
          LY = int(data[6].split("\t")[0]);
          LZ = int(data[7].split("\t")[0]);
          // String steering = data[7]; // Steering direction
          motorL = int(data[1].split("\t")[0]);
          dir_motorL = data[2].split("\t")[0]; // Direction for motorL
          motorR = int(data[3].split("\t")[0]);
          dir_motorR = data[4].split("\t")[0]; // Direction for motorR
    
          // Display the collected data
          print("LX: *" + LX + "* LY: *" + LY + "* LZ: *" + LZ);
          // print(", Steering: " + steering);
          print("* Motor L: *" + motorL + "*  dir_motorL *" + dir_motorL);
          println("* Motor R: *" + motorR + "*  dir_motorR *" + dir_motorR);
        }
      }
    }
  }
}
