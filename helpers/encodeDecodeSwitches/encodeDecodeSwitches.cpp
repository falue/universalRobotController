/*
  This is a test for encoding 4 boolean values (eg., 4 switches or buttons) into an int value
  between 1000 and 2000. Then, it decodes that value and compares both arrays of booleans and gives a verdict.
  Change the jitter value to something bigger than +/-32 to see it fail in action.
  
  This is used over RF, so some jitter is expected. The decoder function
  tries its best to interpret the values approprietly.
  Test like this:
    g++ -o encodeDecodeSwitches encodeDecodeSwitches.cpp && ./encodeDecodeSwitches
*/

#include <iostream>
#include <algorithm> // For std::max and std::min
#include <cmath>    // Include the cmath library for atan2 and constants
 

int map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int encodeButtons(bool state1, bool state2, bool state3, bool state4) {
  // Create a binary number from the button states
  int encodedValue = (state1 << 0) | (state2 << 1) | (state3 << 2) | (state4 << 3);
  // Scale the binary value from 0-15 to 1000-2000
  return map(encodedValue, 0, 15, 1000, 2000);
}

bool* decodeButtons(int encodedValue) {
    // Jitter of +/-32 can be handled
    static bool buttonStates[4];  // Static to preserve state after the function returns

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
    int smallestDifference = std::abs(encodedValue - encodedStates[0]);
    for (int i = 1; i < 16; i++) {
        int diff = std::abs(encodedValue - encodedStates[i]);
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

int randInRange(int min, int max) {
    // Ensure the random number generator is seeded (do this once in your program)
    static bool firstTime = true;
    if (firstTime) {
        srand(time(NULL));
        firstTime = false;
    }

    // Calculate the range size plus one to include max in the result
    int range = max - min + 1;

    // Generate a random number within the range
    return rand() % range + min;
}


bool compareBoolArrays(const bool arr1[], const bool arr2[], int size) {
    for (int i = 0; i < size; ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}


int main() {
    int jitter = randInRange(-32, 32);

    // Test case
    bool testCase[4];  // Create an array of 4 boolean elements
    // Populate the array with random true/false values
    for (int i = 0; i < 4; ++i) {
        testCase[i] = randInRange(0, 1) == 1;
    }
    
    int encoded = encodeButtons(testCase[0], testCase[1], testCase[2], testCase[3]);


    std::cout << "Create 4 random booleans: " << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << (testCase[i] ? "true" : "false") << (i < 3 ? ", " : "");
    }
    std::cout << std::endl;

    std::cout << "=> Encoded (" << encoded << ") + random jitter (" << jitter << "): " <<  encoded + jitter << std::endl;
    std::cout << "" << std::endl;

    std::cout << "Decoded result:         " << std::endl;
    bool* buttons = decodeButtons(encoded + jitter);
    for (size_t i = 0; i < 4; ++i) {
        std::cout << std::boolalpha << buttons[i] << (i < 4 - 1 ? ", " : "");
    }
    std::cout << std::endl;

    std::cout << "" << std::endl;
    bool areEqual = compareBoolArrays(testCase, buttons, 4);
    std::cout << "Arrays are " << (areEqual ? "equal." : "not equal.") << std::endl;
    std::cout << "=> Test " << (areEqual ? "succeeded 🟢" : "failed 🔴") << std::endl;



    return 0;
}
