/*
    Some other outdated script to flesh out the motor speeds
    Test like this:
      g++ -o test_ruleOfThree test_ruleOfThree.cpp && ./test_ruleOfThree 
*/

#include <iostream>
#include <algorithm> // For std::max and std::min
#include <cmath>    // Include the cmath library for atan2 and constants


int ruleOfThree(int a, int b, int c) {
  //
  if (b == 0) { // Check for division by zero
      return 0; // Return zero or an appropriate error value
  }
  int d = (c * b) / a;
  return d;
}

int main() {
    // Test cases
    std::cout << "Testing:" << std::endl;

    std::cout << "ruleOfThree(75, 100, 50) = "
              << ruleOfThree(75, 100, 50) << std::endl;
}