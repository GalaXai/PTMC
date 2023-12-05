	#include <LiquidCrystal.h>
	
	// Initialize the LCD
	LiquidCrystal lcd(2, 12, 1, 3, 9, 19);
	
	void setup() {
	  lcd.begin(16, 2);  // Set the number of LCD columns and rows
	  Serial.begin(9600);  // Start the serial communication
	}
	
	void loop() {
	  float totalResistance = 10.0;  // Initialize total resistance to 10 ohms
	  float voltage = readVoltage(A7);  // Read voltage from A7
	  float current = voltage / totalResistance;  // Calculate current using Ohm's law
	
	  printVoltage(voltage);  // Print the voltage to the LCD
	  printCurrent(current);  // Print the current to the LCD
	  delay(1000);  // Wait for 1 second
	}
	
	float readVoltage(int pin) {
	  int sensorValue = analogRead(pin);
	  return sensorValue * (5.0 / 1023.0);  // Scale the value to voltage
	}
	
	void printCurrent(float current) {
	  lcd.setCursor(0, 1);  // Set the cursor position
	  lcd.print("Current: ");
	  lcd.print(current, 2);  // Print current with two decimal places
	  lcd.print(" A");
	}
	
	void printVoltage(float voltage) {
	  lcd.setCursor(0, 0);  // Set the cursor position
	  lcd.print("Voltage: ");
	  lcd.print(voltage, 2);  // Print voltage with two decimal places
	  lcd.print(" V");
	}
	