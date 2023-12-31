int hourServoPin = 7;
int minuteServoPin = 6;
int secondServoPin = 5;
int soundEffectPin = 31;
int millisecondsPerSecond = 100;

const int stepsPerRevolution = 2;
const int secondStepperPin1 = 47;
const int secondStepperPin2 = 49;
const int secondStepperPin3 = 51;
const int secondStepperPin4 = 53;
int secondStepNumber = 0;

const int minuteStepperPin1 = 39;
const int minuteStepperPin2 = 41;
const int minuteStepperPin3 = 43;
const int minuteStepperPin4 = 45;
int minuteStepNumber = 0;

const int hourStepperPin1 = 46;
const int hourStepperPin2 = 48;
const int hourStepperPin3 = 50;
const int hourStepperPin4 = 52;
int hourStepNumber = 0;

const int shiftDataPin = A0;
const int shiftLatchPin = A1;
const int shiftClockPin = A2;

byte digits[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

void setup() {
  pinMode(hourServoPin, OUTPUT);
  pinMode(minuteServoPin, OUTPUT);
  pinMode(secondServoPin, OUTPUT);
  resetToZeroPosition(hourServoPin);
  resetToZeroPosition(minuteServoPin);
  resetToZeroPosition(secondServoPin);
  pinMode(soundEffectPin, OUTPUT);
  digitalWrite(soundEffectPin, LOW);
  
  pinMode(secondStepperPin1, OUTPUT);
  pinMode(secondStepperPin2, OUTPUT);
  pinMode(secondStepperPin3, OUTPUT);
  pinMode(secondStepperPin4, OUTPUT);
  pinMode(minuteStepperPin1, OUTPUT);
  pinMode(minuteStepperPin2, OUTPUT);
  pinMode(minuteStepperPin3, OUTPUT);
  pinMode(minuteStepperPin4, OUTPUT);
  pinMode(hourStepperPin1, OUTPUT);
  pinMode(hourStepperPin2, OUTPUT);
  pinMode(hourStepperPin3, OUTPUT);
  pinMode(hourStepperPin4, OUTPUT);
}

void loop() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 60; j++) {
      for (int k = 0; k < 60; k++) {
        updateDisplay(i, j, k);      
        updateSecondServo(k);
        operateSecondStepper();
      }
      triggerSound();
      resetToZeroPosition(secondServoPin);
      updateMinuteServo(j);
      operateMinuteStepper();
    }
    resetToZeroPosition(minuteServoPin);
    updateHourServo(i);
    operateHourStepper();
  }
  resetToZeroPosition(hourServoPin);
}
		
void updateDisplay(int hour, int minute, int second) {
  int hourTens = hour / 10;
  int hourUnits = hour % 10;

  int minuteTens = minute / 10;
  int minuteUnits = minute % 10;

  int secondTens = second / 10;
  int secondUnits = second % 10;

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digits[secondUnits]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digits[secondTens]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digits[minuteUnits]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digits[minuteTens]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digits[hourUnits]);
  digitalWrite(shiftLatchPin, HIGH);

  digitalWrite(shiftLatchPin, LOW);
  shiftOut(shiftDataPin, shiftClockPin, MSBFIRST, digits[hourTens]);
  digitalWrite(shiftLatchPin, HIGH);
}


void operateSecondStepper() {
    int steps[8][4] = {
        {HIGH, LOW, LOW, HIGH},
        {LOW, LOW, LOW, HIGH},
        {LOW, LOW, HIGH, HIGH},
        {LOW, LOW, HIGH, LOW},
        {LOW, HIGH, HIGH, LOW},
        {LOW, HIGH, LOW, LOW},
        {HIGH, HIGH, LOW, LOW},
        {HIGH, LOW, LOW, LOW}
    };

    for (int i = 0; i < stepsPerRevolution; i++) {
        digitalWrite(secondStepperPin1, steps[secondStepNumber][0]);
        digitalWrite(secondStepperPin2, steps[secondStepNumber][1]);
        digitalWrite(secondStepperPin3, steps[secondStepNumber][2]);
        digitalWrite(secondStepperPin4, steps[secondStepNumber][3]);

        secondStepNumber++;
        if (secondStepNumber >= 8) {
            secondStepNumber = 0;
        }
    }
}

void operateMinuteStepper() {
    int steps[8][4] = {
        {HIGH, LOW, LOW, HIGH},
        {LOW, LOW, LOW, HIGH},
        {LOW, LOW, HIGH, HIGH},
        {LOW, LOW, HIGH, LOW},
        {LOW, HIGH, HIGH, LOW},
        {LOW, HIGH, LOW, LOW},
        {HIGH, HIGH, LOW, LOW},
        {HIGH, LOW, LOW, LOW}
    };

    for (int i = 0; i < stepsPerRevolution; i++) {
        digitalWrite(minuteStepperPin1, steps[minuteStepNumber][0]);
        digitalWrite(minuteStepperPin2, steps[minuteStepNumber][1]);
        digitalWrite(minuteStepperPin3, steps[minuteStepNumber][2]);
        digitalWrite(minuteStepperPin4, steps[minuteStepNumber][3]);
        minuteStepNumber++;
        if (minuteStepNumber >= 8) {
            minuteStepNumber = 0;
        }
    }
}

void operateHourStepper() {
    int steps[8][4] = {
        {HIGH, LOW, LOW, HIGH},
        {LOW, LOW, LOW, HIGH},
        {LOW, LOW, HIGH, HIGH},
        {LOW, LOW, HIGH, LOW},
        {LOW, HIGH, HIGH, LOW},
        {LOW, HIGH, LOW, LOW},
        {HIGH, HIGH, LOW, LOW},
        {HIGH, LOW, LOW, LOW}
    };

    for (int i = 0; i < stepsPerRevolution; i++) {
        digitalWrite(hourStepperPin1, steps[hourStepNumber][0]);
        digitalWrite(hourStepperPin2, steps[hourStepNumber][1]);
        digitalWrite(hourStepperPin3, steps[hourStepNumber][2]);
        digitalWrite(hourStepperPin4, steps[hourStepNumber][3]);
        hourStepNumber++;
        if (hourStepNumber >= 8) {
            hourStepNumber = 0;
        }
    }
}

void updateHourServo(int hour) {
  float pulseWidth = map(hour, 0, 11, 1000, 2000);
  digitalWrite(hourServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(hourServoPin, LOW);
}

void updateMinuteServo(int minute) {
  float pulseWidth = map(minute, 0, 59, 1000, 2000);
  digitalWrite(minuteServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(minuteServoPin, LOW);
  delayMicroseconds(20000 - pulseWidth);
}

void updateSecondServo(int second) {
  float pulseWidth = map(second, 0, 59, 1000, 2000);
  digitalWrite(secondServoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(secondServoPin, LOW);
  delay(millisecondsPerSecond);
  delayMicroseconds(20000 - pulseWidth);
}

void resetToZeroPosition(int servoPin) {
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(20000 - 1000);
}

void triggerSound() {
  digitalWrite(soundEffectPin, HIGH);
  delay(50);
  digitalWrite(soundEffectPin, LOW);
}
