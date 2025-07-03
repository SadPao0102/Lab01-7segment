// Define the pins connected to each segment of the 7-segment display
// These pins correspond to the connections in your circuit diagram
const int segA = 23;
const int segB = 22;
const int segC = 21;
const int segD = 19;
const int segE = 18;
const int segF = 17; // Corrected based on your diagram, r6 to segF
const int segG = 16; // Corrected based on your diagram, r7 to segG
// Note: Your diagram does not explicitly connect a pin to the Decimal Point (DP) segment.
// If you connect one, you'd add it here and in the segmentPins array.
// const int segDP = 4; // Example if you add a DP connection

// Create an array to hold the pin numbers for easy iteration
// Ensure the order here matches the order in the digitPatterns array (A, B, C, D, E, F, G)
const int segmentPins[] = {segA, segB, segC, segD, segE, segF, segG};
const int NUM_SEGMENTS = sizeof(segmentPins) / sizeof(segmentPins[0]);

// Define the segment patterns for numbers 0-9 (common cathode)
// Each row represents a number, and each column represents a segment (A-G)
// A '1' (HIGH) means the segment is ON, '0' (LOW) means OFF
// The order here must match the 'segmentPins' array: A, B, C, D, E, F, G
const byte digitPatterns[10][7] = {
  //   A  B  C  D  E  F  G
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

void setup() {
  // Initialize all segment pins as OUTPUTs
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void displayDigit(int digit) {
  // Ensure the digit is within the valid range (0-9)
  if (digit < 0 || digit > 9) {
    // Optionally clear the display or show an error
    for (int i = 0; i < NUM_SEGMENTS; i++) {
      digitalWrite(segmentPins[i], LOW); // Turn all segments off
    }
    return;
  }

  // Iterate through each segment and set its state based on the digit pattern
  // For common cathode, HIGH turns segment ON, LOW turns segment OFF
  for (int i = 0; i < NUM_SEGMENTS; i++) {
    digitalWrite(segmentPins[i], digitPatterns[digit][i]);
  }
}

void loop() {
  // Cycle through numbers 0-9, displaying each for 1 second
  for (int digit = 0; digit <= 9; digit++) {
    displayDigit(digit);
    delay(1000); // Wait for 1 second
  }
}
