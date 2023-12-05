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

  // Set relay pins as outputs and turn them off
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], LOW);
  }

  pinMode(currentSensorPin, INPUT); // Set the current sensor pin as input
}

void loop() {
  deactivateAllRelays(); 
  double voltage = readVoltage(A7);  // Read scaled voltage from A7 once per loop
  // float current = readCurrent(currentSensorPin); // Read the current from the current sensor
 

  // Logic to activate relays based on the voltage
  if (voltage == 5.0) {
    int i = 0;
    while (voltage == 5.0 && i < numRelays) {
      activateRelay(i);
		 delay(500);  // Delay to allow the voltage to settle
      voltage = readVoltage(A7);  // Re-read the voltage
      i++;  // Increment the relay counter
    }
	double scaledVoltage = voltage * pow(2, i);
	printVoltage(scaledVoltage);	
  } else {
    deactivateAllRelays();  // If voltage is too low, turn off all relays
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
  digitalWrite(relayPins[relayIndex], LOW);  // Turn on the selected relay
}

void deactivateAllRelays() {
  for (int i = 0; i < numRelays; i++) {
    digitalWrite(relayPins[i], HIGH);  // Turn off all relays
  }
}
