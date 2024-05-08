/*
  Some other outdated script to flesh out the motor speeds
  Test like this:
    g++ -o test_motors test_motors.cpp && ./test_motors 
*/

#include <iostream>
#include <algorithm> // For std::max and std::min
#include <cmath>    // Include the cmath library for atan2 and constants


/* int calculateMotorSpeed(int Y, int X, char motorSide) {
    int baseSpeed = Y; // Speed from the forward/backward joystick input
    int turnAdjustment = X; // Speed adjustment from the left/right joystick input

    if (motorSide == 'L') {
        // Subtract the turn adjustment from the left motor when turning left
        return std::max(0, baseSpeed - abs(turnAdjustment));
    } else if (motorSide == 'R') {
        // Add the turn adjustment to the right motor when turning left
        return std::min(100, baseSpeed + abs(turnAdjustment));
    }
    return 0; // Default return for safety
} */
int map(int x, int in_min, int in_out, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_out - in_min) + out_min;
}

/* int calculateMotorSpeed(int Y, int X, char motorSide) {
    // Proportional reduction based on the turning intensity

    if (motorSide == 'L') {
        return Y = Y + abs(X)/2;  // Reduce left motor speed when turning right
    } else {
        return Y = Y - abs(X)/2;  // Reduce right motor speed when turning left
    }
} */

int calculateMotorSpeedXY(int Y, int X, char motorSide) {
    int val;
    if (motorSide == 'L') {
        val = Y - abs(X)/2;  // Reduce left motor speed when turning right

    } else {
        val = Y + abs(X)/2;  // Reduce right motor speed when turning left
    }
    return val > 100 ? 100 : val;
}

int calculateMotorSpeed(int Y, int X, int Z, char motorSide) {
    int val;
    if (motorSide == 'L') {
        val = Y + X/2;  // + abs(Z)/2;  // Reduce left motor speed when turning right
    } else {
        val = Y - X/2;  // - abs(Z)/2;  // Reduce right motor speed when turning left
    }
    val = val > 100 ? 100 : val;
    val = val < -100 ? -100 : val;

    val = val > std::max(Y, X) ? std::max(Y, X) : val;
    // val = val < std::min(Y, X) ? std::min(Y, X) : val;
    return val;  // Negative values are positive because steering inverses
}
/*

int calculateMotorSpeed(int Y, int X, char motorSide) {
    // Calculate the effective forward speed after adjusting for steering
    int motorSpeed = 0;
    if (motorSide == 'L') {
        motorSpeed = Y + X;
    } else if (motorSide == 'R') {
        motorSpeed = Y - X;
    }

    motorSpeed = map(motorSpeed, 0,100, 0,std::max(Y, X));

    // Ensure motor speed does not exceed Y or drop below 0
    motorSpeed = std::max(0, std::min(Y, motorSpeed));
    return motorSpeed;
} */


// Function to calculate the direction angle from joystick inputs
/* double calculateAngle(int X, int Y) {
    // atan2 gives the angle in radians. We convert it to degrees.
    double angle = atan2(-X, Y) * 180.0 / M_PI;

    // Adjust for negative angles
    if (angle < 0) {
        angle += 360;
    }

    return angle;
} */
/* 
int calculateMotorSpeed(int X, int Y, char motorSide) {
    double theta = atan2(Y, X);  // Get the angle in radians
    double r = sqrt(X * X + Y * Y);  // Euclidean distance formula

    // Normalize radius to a scale of 0 to 100 (assuming max joystick input gives max speed)
    double maxInput = sqrt(100 * 100 + 100 * 100);
    r = (r / maxInput) * 100;

    int leftMotorSpeed = 0;
    int rightMotorSpeed = 0;

    // Calculate motor speeds based on the angle
    leftMotorSpeed = int(r + r * sin(theta - M_PI / 4));
    rightMotorSpeed = int(r + r * cos(theta - M_PI / 4));

    if(leftMotorSpeed > 100) {
        leftMotorSpeed = 100;
        rightMotorSpeed = map(rightMotorSpeed, -100,leftMotorSpeed, -100,100);
    }
    else if(rightMotorSpeed > 100) {
        rightMotorSpeed = 100;
        leftMotorSpeed = map(leftMotorSpeed, -100,rightMotorSpeed, -100,100);
    }

    // Clamping the motor speeds to maximum of 100
    //leftMotorSpeed = std::min(std::max(leftMotorSpeed, -100), 100);
    //rightMotorSpeed = std::min(std::max(rightMotorSpeed, -100), 100);


    if (motorSide == 'L') {
        return leftMotorSpeed;
    } else {
        return rightMotorSpeed;
    }
} */

int main() {
    // Test cases
    std::cout << "Testing Motor Speeds:" << std::endl;

    std::cout << "Y 0 \tX 0:\t\tLeft Motor = "
              << calculateMotorSpeed(0, 0, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(0, 0, 0, 'R') << std::endl;

    std::cout << "Y 10 \tX 0:\t\tLeft Motor = "
              << calculateMotorSpeed(10, 0, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(10, 0, 0, 'R') << std::endl;

    std::cout << "Y 50 \tX 0:\t\tLeft Motor = "
              << calculateMotorSpeed(50, 0, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(50, 0, 0, 'R') << std::endl;

    std::cout << "Y 100 \tX 0:\t\tLeft: Motor = "
              << calculateMotorSpeed(100, 0, 0, 'L')
              << "\tRight Motor = " << calculateMotorSpeed(100, 0, 0, 'R') << std::endl;

    std::cout << "Y 100 \tX -100:\t\tLeft Motor = "
              << calculateMotorSpeed(100, -100, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(100, -100, 0, 'R') << std::endl;

    std::cout << "Y 100 \tX 100:\t\tLeft Motor = "
              << calculateMotorSpeed(100, 100, 0, 'L')
              << "\tRight Motor = " << calculateMotorSpeed(100, 100, 0, 'R') << std::endl;

    std::cout << "Y 100 \tX -66:\t\tLeft Motor = "
              << calculateMotorSpeed(100, -66, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(100, -66, 0, 'R') << std::endl;

    std::cout << "Y 100 \tX 50:\t\tLeft Motor = "
              << calculateMotorSpeed(100, 50, 0, 'L')
              << "\tRight Motor = " << calculateMotorSpeed(100, 50, 0, 'R') << std::endl;

    std::cout << "Y 50 \tX 50:\t\tLeft Motor = "
              << calculateMotorSpeed(50, 50, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(50, 50, 0, 'R') << std::endl;


    std::cout << "-----------" << std::endl;


    std::cout << "Y -100 \tX 0:\t\tLeft Motor = "
              << calculateMotorSpeed(-100, 0, 0, 'L')
              << "\tRight Motor = " << calculateMotorSpeed(-100, 0, 0, 'R') << std::endl;

    std::cout << "Y 0 \tX -100:\t\tLeft Motor = "
              << calculateMotorSpeed(0, -100, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(0, -100, 0, 'R') << std::endl;

    std::cout << "Y 0 \tX 100:\t\tLeft Motor = "
              << calculateMotorSpeed(0, 100, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(0, 100, 0, 'R') << std::endl;

    std::cout << "Y 0 \tX 33:\t\tLeft Motor = "
              << calculateMotorSpeed(0, 33, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(0, 33, 0, 'R') << std::endl;

    std::cout << "Y 0 \tX -12:\t\tLeft Motor = "
              << calculateMotorSpeed(0, -12, 0, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(0, -12, 0, 'R') << std::endl;
/* 




    std::cout << "Y 0 \tX 0\tZ 100:\t\tLeft Motor = "
              << calculateMotorSpeed(0, 0, 100, 'L')
              << "\t\tRight Motor = " << calculateMotorSpeed(0, 0, 100, 'R') << std::endl; */


    return 0;
}
