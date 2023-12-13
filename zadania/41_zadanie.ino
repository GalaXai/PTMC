#include <LiquidCrystal.h>

// Definicje pinów dla klawiatury
const byte ROWS = 4; // cztery rzędy
const byte COLS = 4; // cztery kolumny
byte rowPins[ROWS] = {0, 1, 2, 3}; // połącz do pinów 0, 1, 2, 3 na Arduino
byte colPins[COLS] = {6, 7, 8, 9}; // połącz do pinów 6, 7, 8, 9 na Arduino
char keys[ROWS][COLS] = {
  {'+', '=', '0', 'R'},
  {'-', '1', '2', '3'},
  {'*', '4', '5', '6'},
  {'/', '7', '8', '9'}
};

// Definicje pinów dla wyświetlacza
const int rs = 19, en = 18, d4 = 17, d5 = 16, d6 = 15, d7 = 14;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String currentInput = "";
String firstNumber = "";
String secondNumber = "";
char operation = 0;
boolean newNumber = true;

void setup() {
  // Inicjalizacja pinów klawiatury jako wyjścia
  for (byte i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  // Inicjalizacja pinów klawiatury jako wejścia z włączonym pull-up
  for (byte i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  lcd.begin(16, 2);
  lcd.print("Kalkulator");
}

void loop() {
  char key = getKeyPress();
  if (key != 0) {
    if (isdigit(key) || key == '.') {
      if (newNumber) {
        currentInput = "";
        newNumber = false;
      }
      currentInput += key;
      lcd.clear();
      if (operation != 0) { 	
        lcd.print(firstNumber + operation + currentInput);
      } else {
        lcd.print(currentInput);
      }
    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
      if (currentInput.length() > 0 && firstNumber.length() == 0) {
        firstNumber = currentInput;
        operation = key;
        newNumber = true;
        lcd.clear();
        lcd.print(firstNumber + operation);
      } else if (firstNumber.length() > 0 && currentInput.length() > 0) {
        executeOperation();
        operation = key;
        lcd.clear();
        lcd.print(firstNumber + operation);
      }
    } else if (key == '=') {
      if (firstNumber.length() > 0 && currentInput.length() > 0 && operation != 0) {
        executeOperation();
        newNumber = true;
      }
    } else if (key == 'R') {
      resetCalculator();
    }
  }
}

char getKeyPress() {
  for (byte col = 0; col < COLS; col++) {
    digitalWrite(rowPins[col], LOW);
    for (byte row = 0; row < ROWS; row++) {
      if (digitalRead(colPins[row]) == LOW) {
        while (digitalRead(colPins[row]) == LOW); // Oczekiwanie na zwolnienie klawisza
        digitalWrite(rowPins[col], HIGH);
        return keys[row][col];
      }
    }
    digitalWrite(rowPins[col], HIGH);
  }
  return 0; // Brak naciśnięcia klawisza
}

void executeOperation() {
  float num1 = firstNumber.toFloat();
  float num2 = currentInput.toFloat();
  float result = 0;

  switch (operation) {
    case '+': result = num1 + num2; break;
    case '-': result = num1 - num2; break;
    case '*': result = num1 * num2; break;
    case '/': result = num2 != 0 ? num1 / num2 : 0; break;
  }

  lcd.clear();
  lcd.print(result);
  firstNumber = String(result);
  currentInput = "";
  operation = 0;
  newNumber = true;
}


void resetCalculator() {
  currentInput = "";
  firstNumber = "";
  secondNumber = "";
  operation = 0;
  newNumber = true;
  lcd.clear();
  lcd.print("Kalkulator");
}