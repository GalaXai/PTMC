const int cathodeLeds[] = {17, 18, 19};
const int anodeLeds[] = {A13, A14, A15};

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++) {
    pinMode(cathodeLeds[i], OUTPUT);
    pinMode(anodeLeds[i], OUTPUT);
  }
	//digitalWrite(A1,LOW);
	//pinMode(A1,INPUT);
	//A1,3,9
	int lazyPins[] = {2, A2, A9};
	writePins(lazyPins, sizeof(lazyPins) / sizeof(lazyPins[0]), HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int A1State = digitalRead(A1);
  int pin3State = digitalRead(3);
  int pin9State = digitalRead(9);

  if (A1State == LOW || pin3State == LOW || pin9State == LOW) {
    writePins(anodeLeds, sizeof(anodeLeds) / sizeof(anodeLeds[0]), HIGH);
    writePins(cathodeLeds, sizeof(cathodeLeds) / sizeof(cathodeLeds[0]), LOW);
  } else if (A1State == HIGH && pin3State == HIGH && pin9State == HIGH) {
    writePins(anodeLeds, sizeof(anodeLeds) / sizeof(anodeLeds[0]), LOW);
    writePins(cathodeLeds, sizeof(cathodeLeds) / sizeof(cathodeLeds[0]), HIGH);
  }
}

void writePins(const int pins[], int numPins, bool value) {
  for (int i = 0; i < numPins; i++) {
    digitalWrite(pins[i], value);
  }
}