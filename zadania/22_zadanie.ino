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
    byte grayValue = readGrayInput();
    byte binaryValue = grayToBinary(grayValue);

    displayNumber(binaryValue / 10, firstDisplayPins); // Tens digit
    displayNumber(binaryValue % 10, secondDisplayPins); // Ones digit

    digitalWrite(firstDisplayDecimalPin, indexNumberSum >= 10 ? HIGH : LOW);
    digitalWrite(secondDisplayDecimalPin, indexNumberSum % 2 != 0 ? HIGH : LOW);

    delay(5);
}


byte grayToBinary(byte grayValue) {
    byte binaryValue = 0;
    while (grayValue > 0) {
        binaryValue ^= grayValue;
        grayValue >>= 1;
    }
    return binaryValue;
}

byte readGrayInput() {
    byte grayValue = 0;
    for (int i = 0; i < 8; i++) {
        if (digitalRead(inputPins[i]) == LOW) { // Assuming active-low buttons
            grayValue |= (1 << i);
        }
    }
    return grayValue;
}


void displayNumber(byte number, const int displayPins[]) {
  byte segments = segmentValues[number];
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPins[i], segments & (1 << i));
  }
}
