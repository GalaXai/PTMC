#define red_car A2
#define yellow_car 3
#define green_car A9
#define red_guy 2
#define green_guy 1

void setup() {
  pinMode(red_car, OUTPUT);
  pinMode(yellow_car, OUTPUT);
  pinMode(green_car, OUTPUT);
  pinMode(red_guy, OUTPUT);
  pinMode(green_guy, OUTPUT);

 // Light up all LEDs for 2 seconds
 setLights(HIGH, HIGH, HIGH, HIGH, HIGH);
 delay(2000);
 setLights(LOW, LOW, LOW, LOW, LOW);
}

void loop() {
  Sequence();
  Sequence();
  nightMode();
}

void greenForCarsRedForPedestrians() {
  setLights(LOW, LOW, HIGH, HIGH, LOW);
  delay(5000); // Czas trwania zielonego światła dla samochodów
}

void yellowThenRedForCarsGreenForPedestrians() {
  setLights(LOW, HIGH, LOW, HIGH, LOW);
  delay(2000);
  setLights(HIGH, LOW, LOW, HIGH, LOW);
	delay(1000);
  setLights(HIGH, LOW, LOW, LOW, HIGH);
  delay(5000);
}

void blinkingGreenForCars() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(green_guy, HIGH);
    delay(500);
    digitalWrite(green_guy, LOW);
    delay(500);
  }
  setLights(HIGH, HIGH, LOW, HIGH, LOW);
  delay(2000);
  setLights(LOW, LOW, HIGH, HIGH, LOW);
}

void Sequence(){
  greenForCarsRedForPedestrians();
  yellowThenRedForCarsGreenForPedestrians();
  blinkingGreenForCars();
}

void nightMode() {
  setLights(LOW, LOW, LOW, LOW, LOW);
  for (int j = 0; j < 10; j++) {
    digitalWrite(yellow_car, HIGH);
    delay(500);
    digitalWrite(yellow_car, LOW);
    delay(500);
  }
  setLights(LOW, LOW, LOW, LOW, LOW); // Wygaszenie wszystkich świateł
}

void setLights(bool redCarState, bool yellowCarState, bool greenCarState, bool redPedestrianState, bool greenPedestrianState) {
  digitalWrite(red_car, redCarState);
  digitalWrite(yellow_car, yellowCarState);
  digitalWrite(green_car, greenCarState);
  digitalWrite(red_guy, redPedestrianState);
  digitalWrite(green_guy, greenPedestrianState);
}
