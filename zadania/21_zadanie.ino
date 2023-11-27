const int inputPins[] = {0,1,2,3,4,5,6,7}; // Adjust pin numbers as needed
const int indexNumberSum = 2 + 2 + 1 + 3 + 9 + 9; // equals 26
// Define the output pins for the two 7-segment displays
const int firstDisplayPins[] = {A15, A14, A13, A12, A11, A10, A9};
const int secondDisplayPins[] = {A6, A5, A4, A3, A2, A1, A0};
const int firstDisplayDecimalPin = A8;
const int secondDisplayDecimalPin = A7;
const byte segmentValues[] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
  // Add additional patterns for A-F if you are using hexadecimal inputs
};

void setup() {
  // Initialize the segment pins as outputs
  for (int i = 0; i < 8; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }
  pinMode(firstDisplayDecimalPin, OUTPUT);
  pinMode(secondDisplayDecimalPin, OUTPUT);

  // Initialize the input pins as inputs with pull-up resistors
  for (int i = 0; i < 7; i++) {
    pinMode(firstDisplayPins[i], OUTPUT);
    pinMode(secondDisplayPins[i], OUTPUT);
  }
}

void loop() {
  byte binaryValue = readBinaryInput();
  
  // Display the tens and ones digits on the respective displays
  displayNumber(binaryValue / 10, firstDisplayPins); // Tens digit
  displayNumber(binaryValue % 10, secondDisplayPins); // Ones digit

  // Control the decimal point on the first display based on the sum of the index number
  digitalWrite(firstDisplayDecimalPin, indexNumberSum >= 10 ? HIGH : LOW);
  
  // Control the decimal point on the second display based on the parity of the sum of the index number
  digitalWrite(secondDisplayDecimalPin, indexNumberSum % 2 != 0 ? HIGH : LOW);

  delay(5); // Small delay to stabilize display
}


byte readBinaryInput() {
  byte value = 0; // Use byte instead of int
  for (int i = 0; i < 8; i++) {
    // Note the use of INPUT_PULLUP - a pressed switch reads LOW
    if (digitalRead(inputPins[i]) == LOW) {
      value |= (1 << i);
    }
  }
  return value;
}

void displayNumber(byte number, const int displayPins[]) {
  byte segments = segmentValues[number];
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPins[i], segments & (1 << i));
  }
}
