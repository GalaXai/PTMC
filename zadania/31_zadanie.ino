#include <LiquidCrystal.h>

// Inicjalizacja wyświetlacza LCD 
const int rs = 2, en = 12, d4 = 1, d5=3, d6=9, d7= 19;
LiquidCrystal lcd(2, 12, 1, 3, 9, 19); 
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

void setup() {
  lcd.begin(16, 2);  // Ustawienie liczby kolumn i wierszy wyświetlacza
	pinMode(A0,INPUT);
}

void loop() {
  int sensorValue = analogRead(A0);  // Odczyt z ADC
  float voltage = sensorValue * (5.0 / 1023.0);  // Konwersja na napięcie
  lcd.setCursor(0, 0);  // Ustawienie kursora
  lcd.print("Napiecie: ");
  lcd.print(voltage);
  lcd.print(" V");
  delay(1000);  // Aktualizacja co 1 sekundę
}
