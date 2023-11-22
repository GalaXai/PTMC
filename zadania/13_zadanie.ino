#define red_car A2
#define yellow_car 3
#define green_car A9
#define red_guy 2
#define green_guy 1
#define buttonPin 9
#define greenButtonPin 18
#define greenButtonLed 16

volatile bool greenButtonPressed = false;
unsigned long lastGreenButtonPress = 0;

void setup() {
 pinMode(red_car, OUTPUT);
 pinMode(yellow_car, OUTPUT);
 pinMode(green_car, OUTPUT);
 pinMode(red_guy, OUTPUT);
 pinMode(green_guy, OUTPUT);
 pinMode(buttonPin, INPUT_PULLUP); 
 pinMode(greenButtonPin, INPUT_PULLUP);
 pinMode(greenButtonLed, OUTPUT);


  // Light up all LEDs for 2 seconds
 setLights(HIGH, HIGH, HIGH, HIGH, HIGH);
 delay(2000);
 setLights(LOW, LOW, LOW, LOW, LOW);

 attachInterrupt(digitalPinToInterrupt(greenButtonPin), greenButtonInterrupt, FALLING);
}

void loop() {
 if (greenButtonPressed) {
    greenButtonPressed = false; // Reset the flag

    // Check the timing for the green light sequence
    unsigned long currentTime = millis();
    if (currentTime - lastGreenButtonPress < 30000) {
      delay(5000); // Delay the green light sequence
    }
    lastGreenButtonPress = currentTime;

    // Execute the green light sequence
    digitalWrite(greenButtonLed, HIGH); // Turn on the LED
    yellowThenRedForCarsGreenForPedestrians();
    blinkingGreenForCars();
    digitalWrite(greenButtonLed, LOW); // Turn off the LED
  }
  greenForCarsRedForPedestrians();

  // The rest of your loop code (like Sequence() and nightMode())
}

void greenForCarsRedForPedestrians() {
 setLights(LOW, LOW, HIGH, HIGH, LOW);
 checkButtonAndDelay(5000);
}

void yellowThenRedForCarsGreenForPedestrians() {
 setLights(LOW, HIGH, LOW, HIGH, LOW);
 checkButtonAndDelay(2000);
 setLights(HIGH, LOW, LOW, HIGH, LOW);
 checkButtonAndDelay(1000);
 setLights(HIGH, LOW, LOW, LOW, HIGH);
 checkButtonAndDelay(5000);
}

void blinkingGreenForCars() {
 for (int i = 0; i < 5; i++) {
   setLights(HIGH, LOW, LOW, LOW, LOW);
   checkButtonAndDelay(500);
   setLights(HIGH, LOW, LOW, LOW, HIGH);
   checkButtonAndDelay(500);
 }
 setLights(HIGH, HIGH, LOW, HIGH, LOW);
 checkButtonAndDelay(2000);
 setLights(LOW, LOW, HIGH, HIGH, LOW);
 checkButtonAndDelay(2000);
}

void Sequence(){
 greenForCarsRedForPedestrians();
 yellowThenRedForCarsGreenForPedestrians();
 blinkingGreenForCars();
}

void nightMode() {
 setLights(LOW, LOW, LOW, LOW, LOW); // Wyłączenie wszystkich świateł
 while(digitalRead(buttonPin) == LOW) { // Utrzymywanie trybu nocnego dopóki przycisk jest naciśnięty
   setLights(LOW, HIGH, LOW, LOW, LOW); // Włączenie żółtego światła dla samochodów
   delay(500);
   setLights(LOW, LOW, LOW, LOW, LOW);  // Wyłączenie wszystkich świateł
   delay(500);
 }
}

void greenButtonInterrupt() {
  greenButtonPressed = !greenButtonPressed; // Toggle the flag
}

void setLights(bool redCarState, bool yellowCarState, bool greenCarState, bool redPedestrianState, bool greenPedestrianState) {
 digitalWrite(red_car, redCarState);
 digitalWrite(yellow_car, yellowCarState);
 digitalWrite(green_car, greenCarState);
 digitalWrite(red_guy, redPedestrianState);
 digitalWrite(green_guy, greenPedestrianState);
}

void checkButtonAndDelay(long duration) {
 for (long i = 0; i < duration; i += 100) {
   if (digitalRead(buttonPin) == LOW) {
     nightMode();
     break;
   }
   delay(100);
 }
}
