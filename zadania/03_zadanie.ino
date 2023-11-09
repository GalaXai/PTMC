volatile bool toggle = true;

void setup() {
	pinMode(2,INPUT_PULLUP);
	pinMode(LED_BUILTIN,OUTPUT);
	attachInterrupt(0,interruptService,LOW);
}

void loop() {
}


void interruptService(){
	toggle != toggle;
	digitalWrite(LED_BUILTIN,toggle);
}