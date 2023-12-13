#include <LiquidCrystal.h>

// Initialize the LCD
LiquidCrystal lcd(2, 12, 1, 3, 9, 19);

// Relay pins connected to the Arduino
const int relayPins[] = {A0, A1, A2, A3, A4, A5, A6};
const int numRelays = 7;
const int currentSensorPin = A8; // Current sensor connected to A8

void setup() {
  lcd.begin(16, 2);  // Set the number of LCD columns and rows
  Serial.begin(9600);  // Start the serial communication

  // Set relay pins as outputs and turn them on (activate) by default
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);  // Set relays to LOW (deactivated)
  }

  pinMode(currentSensorPin, OUTPUT); // Set the current sensor pin as input
  // Setup lcd
  lcd.setCursor(0, 0);  // Set the cursor position
  lcd.print("Voltage: ");
  
}

void loop() {
  // delay(5000);
  double voltage = readVoltage(A7);  // Read scaled voltage from A7 once per loop

  // Logic to activate relays based on the voltage
  if (voltage < 2.5) {
    for (int i = 7; 2.5 > readVoltage(A7); i--) {
      activateRelay(i);
		 delay(1000);
    }
    double scaledVoltage = voltage * pow(2, numRelays);
    printVoltage(scaledVoltage);
  } else {
	delay(1000);    
  deactivateAllRelays();  // If voltage is high enough, turn off all relays
  }
  delay(1000);  // Wait for 1 second before next loop iteration
}

double readVoltage(int pin) {
  int sensorValue = analogRead(pin);
  float voltage = sensorValue * (5.0 / 1023.0);  // Scale the value
  return voltage;
}

void printVoltage(float voltage) {
  lcd.setCursor(0, 0);  // Set the cursor position
  lcd.print("Voltage: ");
  lcd.print(voltage);
  lcd.print("V");
}

void activateRelay(int relayIndex) {
  digitalWrite(relayPins[relayIndex], HIGH);  // Activate the selected relay
}

void deactivateAllRelays() {
  for (int i = 0; i < numRelays; i++) {
    digitalWrite(relayPins[i], LOW);  // Deactivate all relays
  }
}
