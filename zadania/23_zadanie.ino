// Define the output pins for the two 7-segment displays
const int firstDisplayPins[] = {A15, A14, A13, A12, A11, A10, A9};
const int secondDisplayPins[] = {A6, A5, A4, A3, A2, A1, A0};

// Define the pins for the decimal points on the first and second displays
const int firstDisplayDecimalPin = A8;
const int secondDisplayDecimalPin = A7;

// Define the input pins for the code input
const int inputPins[] = {0, 1, 2, 3, 4, 5, 6, 7};

// Define the selector switch input pins
const int selectorPins[] = {31, 33, 35};

// Define a binary to 7-segment display mapping for hexadecimal digits
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
  B01101111, // 9
  B01110111, // A
  B01111100, // B
  B00111001, // C
  B01011110, // D
  B01111001, // E
  B01110001  // F
};


// Function prototypes
int readSelectorSwitch();
byte readInput();
byte binaryToDecimal(byte binaryValue);
byte grayToDecimal(byte grayValue);
void binaryToHex(byte binaryValue, char* hexValue);
void grayToHex(byte grayValue, char* hexValue);
byte aikenToDecimal(byte aikenValue);
void aikenToHex(byte aikenValue, char* hexValue);
byte johnsonToDecimal(byte johnsonValue);
void johnsonToHex(byte johnsonValue, char* hexValue);
void displayNumber(byte number, const int displayPins[]);
void displayHex(char* hexValue, const int displayPinsTens[], const int displayPinsOnes[]);


void setup() {
  // Initialize binary input pins
  for (int i = 0; i < 8; i++) {
    pinMode(inputPins[i], INPUT_PULLUP);
  }

  // Initialize selector switch pins
  for (int i = 0; i < 3; i++) {
    pinMode(selectorPins[i], INPUT_PULLUP);
  }

  // Initialize display pins
  for (int i = 0; i < 7; i++) {
    pinMode(firstDisplayPins[i], OUTPUT);
    pinMode(secondDisplayPins[i], OUTPUT);
  }

  // Initialize decimal point pins
  pinMode(firstDisplayDecimalPin, OUTPUT);
  pinMode(secondDisplayDecimalPin, OUTPUT);
}

void loop() {
  int selectorValue = readSelectorSwitch();
  byte inputValue = readInput();
  char hexValue[2]; // To store hexadecimal values

  switch (selectorValue) {
    case 0:
      // Binary to decimal
      displayNumber(binaryToDecimal(inputValue), firstDisplayPins, secondDisplayPins);
      break;
    case 1:
      // Gray to decimal
      displayNumber(grayToDecimal(inputValue), firstDisplayPins, secondDisplayPins);
      break;
    case 2:
      // Binary to hexadecimal
      binaryToHex(inputValue, hexValue);
      displayHex(hexValue, firstDisplayPins, secondDisplayPins);
      break;
    case 3:
      // Gray to hexadecimal
      grayToHex(inputValue, hexValue);
      displayHex(hexValue, firstDisplayPins, secondDisplayPins);
      break;
    case 4:
      // AIKEN to decimal
      displayNumber(aikenToDecimal(inputValue), firstDisplayPins, secondDisplayPins);
      break;
    case 5:
      // AIKEN to hexadecimal
      aikenToHex(inputValue, hexValue);
      displayHex(hexValue, firstDisplayPins, secondDisplayPins);
      break;
    case 6:
      // JOHNSON to decimal
      displayNumber(johnsonToDecimal(inputValue), firstDisplayPins, secondDisplayPins);
      break;
    case 7:
      // JOHNSON to hexadecimal
      johnsonToHex(inputValue, hexValue);
      displayHex(hexValue, firstDisplayPins, secondDisplayPins);
      break;
  }

  // Update decimal points based on the index number sum condition
  updateDecimalPoints();

  delay(5); // Small delay for stability
}

// Read the selector switch value
int readSelectorSwitch() {
  int value = 0;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(selectorPins[i]) == LOW) {
      value |= (1 << i);
    }
  }
  return value;
}

// Read the input pins for the binary/Gray/AIKEN/JOHNSON code
byte readInput() {
  byte value = 0;
  for (int i = 0; i < 8; i++) {
    if (digitalRead(inputPins[i]) == LOW) {
      value |= (1 << i);
    }
  }
  return value;
}
// Utility function to update decimal points based on the index number sum
void updateDecimalPoints() {
  const int indexNumberSum = 2 + 2 + 1 + 3 + 9 + 9; // equals 26
  digitalWrite(firstDisplayDecimalPin, indexNumberSum >= 10 ? HIGH : LOW);
  digitalWrite(secondDisplayDecimalPin, indexNumberSum % 2 != 0 ? HIGH : LOW);
}

// Function to display a number in decimal on the 7-segment displays
void displayNumber(byte number, const int displayPinsTens[], const int displayPinsOnes[]) {
  // Split the number into tens and ones for display
  byte tens = number / 10;
  byte ones = number % 10;
  
  // Display tens digit
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPinsTens[i], segmentValues[tens] & (1 << i));
  }

  // Display ones digit
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPinsOnes[i], segmentValues[ones] & (1 << i));
  }
}


// Function to convert and display a hexadecimal number on the 7-segment displays
void displayHex(char* hexValue, const int displayPinsTens[], const int displayPinsOnes[]) {
  // Display the tens digit (first half-byte in hexadecimal)
  byte tensDigit = (hexValue[0] <= '9') ? hexValue[0] - '0' : hexValue[0] - 'A' + 10;
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPinsTens[i], segmentValues[tensDigit] & (1 << i));
  }

  // Display the ones digit (second half-byte in hexadecimal)
  byte onesDigit = (hexValue[1] <= '9') ? hexValue[1] - '0' : hexValue[1] - 'A' + 10;
  for (int i = 0; i < 7; i++) {
    digitalWrite(displayPinsOnes[i], segmentValues[onesDigit] & (1 << i));
  }
}

// Function to convert binary to decimal (assuming a byte is already in binary)
byte binaryToDecimal(byte binaryValue) {
  return binaryValue; // In this context, the input is already binary
}

// Function to convert Gray code to binary, then to decimal
byte grayToBinary(byte grayValue) {
  byte binaryValue = grayValue;
  for (byte mask = grayValue >> 1; mask != 0; mask >>= 1) {
    binaryValue ^= mask;
  }
  return binaryValue;
}


// Convert binary value to hexadecimal characters
void binaryToHex(byte binaryValue, char* hexValue) {
  const char hexChars[] = "0123456789ABCDEF";
  hexValue[0] = hexChars[(binaryValue >> 4) & 0x0F]; // Extracting the upper nibble (4 bits)
  hexValue[1] = hexChars[binaryValue & 0x0F];        // Extracting the lower nibble
  hexValue[2] = '\0'; // Null-terminate the string
}

// Convert Gray code to binary, then to hexadecimal characters
void grayToHex(byte grayValue, char* hexValue) {
  byte binaryValue = grayToBinary(grayValue);
  binaryToHex(binaryValue, hexValue);
}



byte aikenToDecimal(byte aikenValue) {
    // Extracting the first four bits and applying the respective weights
    byte firstBit = (aikenValue >> 3) & 1; // 2 times
    byte secondBit = (aikenValue >> 2) & 1; // 4 times
    byte thirdBit = (aikenValue >> 1) & 1; // 2 times
    byte fourthBit = aikenValue & 1; // 1 time

    // Calculate the weighted sum
    byte result = firstBit * 2 + secondBit * 4 + thirdBit * 2 + fourthBit * 1;

    return result;
}


// Convert AIKEN code to hexadecimal characters
void aikenToHex(byte aikenValue, char* hexValue) {
  byte decimalValue = aikenToDecimal(aikenValue);
  binaryToHex(decimalValue, hexValue);
}

byte johnsonToDecimal(byte johnsonValue) {
    byte distanceFromLSB = 0;
    byte distanceFromMSB = 0;
    bool foundOne = false;

    
    // Count distance from MSB to first 1
    for (int i = 7; i >= 0; i--) {
        if ((johnsonValue >> i) & 1) {
            distanceFromMSB = i;
            foundOne = true;
            break;
        }
    }
    
    // Count distance from LSB to first 1
    for (int i = 0; i < 8; i++) {
        if ((johnsonValue >> i) & 1) {
            distanceFromLSB = i + 1;
            break;
        }
    }

    

    // Calculate and return the result or 0 if no 1's were found
    return foundOne ? distanceFromLSB + distanceFromMSB : 0;
}


// Convert JOHNSON code to hexadecimal characters
void johnsonToHex(byte johnsonValue, char* hexValue) {
  byte decimalValue = johnsonToDecimal(johnsonValue);
  binaryToHex(decimalValue, hexValue);
}

byte grayToDecimal(byte grayValue) {
  // Convert Gray code to binary first
  byte binaryValue = grayToBinary(grayValue);
  
  // For a byte, the binary value is the same as the decimal value
  return binaryValue;
}
