int hourServoPin = 7;
int minuteServoPin = 6;
int secondServoPin = 5;
int soundEffectPin = 31;
int milliSecondsInSecond = 100;

const int shiftDataPin = A0;
const int shiftLatchPin = A1;
const int shiftClockPin = A2;

byte digitPatterns[10] = {
  B00111111,
  B00000110,
  B01011011,
  B01001111,
  B01100110,
  B01101101,
  B01111101,
  B00000111,
  B01111111,
  B01101111
};

void setup() {
  pinMode(hourServoPin, OUTPUT);
  pinMode(minuteServoPin, OUTPUT);
  pinMode(secondServoPin, OUTPUT);
  resetToInitialPosition(hourServoPin);
  delayMicroseconds(20000);
  resetToInitialPosition(minuteServoPin);
  delayMicroseconds(20000);
  resetToInitialPosition(secondServoPin);
  delayMicroseconds(20000);
  pinMode(soundEffectPin, OUTPUT);
  digitalWrite(soundEffectPin, LOW);
}

void loop() {
  for (int hour = 0; hour < 12; hour++) {
    for (int minute = 0; minute < 60; minute++) {
      for (int second = 0; second < 60; second++) {
        updateDisplay(hour, minute, second);
        moveSecondHand(second);
      }
      playSound();
      resetToInitialPosition(secondServoPin);
      moveMinuteHand(minute);
    }
    resetToInitialPosition(minuteServoPin);
    moveHourHand(hour);
  }
  resetToInitialPosition(hourServoPin);
}

void updateDisplay(int hour, int minute, int second) {
  int hourTens = hour / 10;
  int hourUnits = hour % 10;
  int minuteTens = minute / 10;
  int minuteUnits = minute % 10;
  int secondTens = second / 10;
  int secondUnits = second % 10;

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digitPatterns[secondUnits]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digitPatterns[secondTens]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digitPatterns[minuteUnits]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digitPatterns[minuteTens]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digitPatterns[hourUnits]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digitPatterns[hourTens]);
  digitalWrite(shiftLatchPin, HIGH);
}

void moveHourHand(int hour) {
  float pulseWidth = map(hour, 0, 11, 1000, 2000);
  digitalWrite(hourServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(hourServoPin, LOW);
}

void moveMinuteHand(int minute) {
  float pulseWidth = map(minute, 0, 59, 1000, 2000);
  digitalWrite(minuteServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(minuteServoPin, LOW);
  delayMicroseconds(20000 - pulseWidth);
}

void moveSecondHand(int second) {
  float pulseWidth = map(second, 0, 59, 1000, 2000);
  digitalWrite(secondServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(secondServoPin, LOW);
  delay(milliSecondsInSecond);
  delayMicroseconds(20000 - pulseWidth);
}

void resetToInitialPosition(int servoPin) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(20000 - 1000);
}

void playSound() {
  digitalWrite(soundEffectPin, HIGH);
  delay(50);
  digitalWrite(soundEffectPin, LOW);
}
