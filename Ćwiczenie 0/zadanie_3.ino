bool toogle = false;

void setup() {
	pinMode(A15, OUTPUT); 
	pinMode(A14, OUTPUT); 
	pinMode(A13, OUTPUT); 
	pinMode(21, INPUT);
	pinMode(20, INPUT);
	pinMode(19, INPUT);
	
	pinMode(2, INPUT_PULLUP); 
	pinMode(3, INPUT_PULLUP);
	pinMode(A2, INPUT_PULLUP);
	
	pinMode(13, OUTPUT);
	attachInterrupt(4, funkcjaPrzerwania, RISING);
}

void loop() {
	if(digitalRead(4) == LOW || digitalRead(9) == LOW || digitalRead(A1) == LOW){ 
		pinMode(20, OUTPUT);
		pinMode(19, OUTPUT);
		pinMode(21, OUTPUT);
		digitalWrite(A15, HIGH);
		digitalWrite(A14, HIGH);
		digitalWrite(A13, HIGH);
	}
	else{
		pinMode(21, INPUT);
		pinMode(20, INPUT);
		pinMode(19, INPUT);
		digitalWrite(A15, LOW);
		digitalWrite(A14, LOW);
		digitalWrite(A13, LOW);
	}
}

void funkcjaPrzerwania() {
	toogle = !toogle; 
	digitalWrite(13, toogle);
}




