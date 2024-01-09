#define PEOPLE_RED A4
#define PEOPLE_GREEN A0
#define CARS_RED A15
#define CARS_YELLOW A12
#define CARS_GREEN A9
#define NIGHT_ON_PIN 13
#define BUTTON_PIN 1
#define LED_PIN 6

void setup() {
  pinMode(CARS_RED, OUTPUT);
  pinMode(CARS_YELLOW, OUTPUT);
  pinMode(CARS_GREEN, OUTPUT);
  pinMode(PEOPLE_RED, OUTPUT);
  pinMode(PEOPLE_GREEN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // TEST
  turnOnOffAll(HIGH);
  delay(1000);
  turnOnOffAll(LOW);
  delay(1000);

  // PRZERWANIA
  pinMode(NIGHT_ON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(NIGHT_ON_PIN), przerwanie, FALLING);
  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), przerwanie, FALLING);
  interrupts();
}

void loop() {
  // jeżeli tryb nocny ON
  if(digitalRead(NIGHT_ON_PIN) == LOW){
     digitalWrite(CARS_GREEN, LOW);
    	digitalWrite(PEOPLE_RED, LOW);
    	digitalWrite(CARS_YELLOW, HIGH);
    	delay(500);
    	digitalWrite(CARS_YELLOW, LOW);
    	delay(500);
  }
  // jeżeli tryb nocny OFF
  else{
    // kliknięto przycisk
    if((digitalRead(BUTTON_PIN) == LOW)){
      digitalWrite(LED_PIN, HIGH);
	delay(2000);
     digitalWrite(CARS_GREEN, LOW);
	digitalWrite(CARS_YELLOW, HIGH);
	delay(2000);
	digitalWrite(CARS_YELLOW, LOW);
    	digitalWrite(CARS_RED, HIGH);
	delay(2000);
	digitalWrite(PEOPLE_RED, LOW);
	digitalWrite(PEOPLE_GREEN, HIGH);
	digitalWrite(LED_PIN, LOW);
	delay(5000);
	for(int i=0; i<5; i++){
		digitalWrite(PEOPLE_GREEN, HIGH); 
		delay(500);
		digitalWrite(PEOPLE_GREEN, LOW);
		delay(500); 
	}
	digitalWrite(PEOPLE_RED, HIGH);
	delay(2000);
	digitalWrite(CARS_RED, LOW);
	digitalWrite(CARS_YELLOW, HIGH);
	delay(1000);
	digitalWrite(CARS_YELLOW, LOW); 
    }
    // przycisk nie aktywny
    else{
      digitalWrite(CARS_YELLOW, LOW);
      digitalWrite(CARS_GREEN, HIGH);
      digitalWrite(PEOPLE_RED, HIGH);
    }
  }
}

void przerwanie() {
  return;
}

void turnOnOffAll(int state) {
  digitalWrite(CARS_RED, state);
  digitalWrite(CARS_YELLOW, state);
  digitalWrite(CARS_GREEN, state);
  digitalWrite(PEOPLE_RED, state);
  digitalWrite(PEOPLE_GREEN, state);
  digitalWrite(LED_PIN, state);
}
