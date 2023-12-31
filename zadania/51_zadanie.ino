// Pin connections for hour, minute, and second servos
int hourServoPin = 7;
int minuteServoPin = 6;
int secondServoPin = 5;

// Function prototypes
void resetToZeroPosition(int servoPin);
void updateHourServo(int hour);
void updateMinuteServo(int minute);
void updateSecondServo(int second);
void triggerSound();

void setup() {
  // Initialize the servo pins as output
  pinMode(hourServoPin, OUTPUT);
  pinMode(minuteServoPin, OUTPUT);
  pinMode(secondServoPin, OUTPUT);

  // Reset all servos to zero position
  resetToZeroPosition(hourServoPin);
  resetToZeroPosition(minuteServoPin);
  resetToZeroPosition(secondServoPin);

  // Initialize sound pin and set to LOW initially
  pinMode(41, OUTPUT);
  digitalWrite(41, LOW);
}

void loop() {
  // Loop through each hour
  for (int hour = 0; hour < 12; hour++) {
    // Loop through each minute
    for (int minute = 0; minute < 60; minute++) {
      // Loop through each second
      for (int second = 0; second < 60; second++) {
        updateSecondServo(second);
      }
      // Trigger sound at the start of each minute
      triggerSound();

      // Reset second servo and update minute servo
      resetToZeroPosition(secondServoPin);
      updateMinuteServo(minute);
    }

    // Reset minute servo and update hour servo
    resetToZeroPosition(minuteServoPin);
    updateHourServo(hour);
  }

  // Reset hour servo after completing 12-hour cycle
  resetToZeroPosition(hourServoPin);
}

void resetToZeroPosition(int servoPin) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(1000); // Zero position pulse width
  digitalWrite(servoPin, LOW);
}

void updateHourServo(int hour) {
  int pulseWidth = map(hour, 0, 11, 1000, 2000);
  digitalWrite(hourServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(hourServoPin, LOW);
}

void updateMinuteServo(int minute) {
  int pulseWidth = map(minute, 0, 59, 1000, 2000);
  digitalWrite(minuteServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(minuteServoPin, LOW);
}

void updateSecondServo(int second) {
  int pulseWidth = map(second, 0, 59, 1000, 2000);
  digitalWrite(secondServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(secondServoPin, LOW);
  delay(100); // Delay to pace the ticking of seconds
}

void triggerSound() {
  digitalWrite(41, HIGH); // Sound on
  delay(50);              // Sound duration
  digitalWrite(41, LOW);  // Sound off
}
