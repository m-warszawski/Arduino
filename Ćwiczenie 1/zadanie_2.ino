#define people_red A4
#define people_green A0
#define cars_red A15
#define cars_yellow A12
#define cars_green A9

void setup(){
	pinMode(cars_red, OUTPUT);  
	pinMode(cars_yellow, OUTPUT);	
	pinMode(cars_green, OUTPUT); 
	pinMode(people_red, OUTPUT);	 
	pinMode(people_green, OUTPUT);
	
	// TEST
	turnOnOffAll(HIGH);
	delay(1000);
	turnOnOffAll(LOW);	
	delay(1000);
	
	// PRZERWANIE
	pinMode(13, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(13), nightMode, FALLING);
	interrupts();
}

void loop(){		
	if(digitalRead(13)==1){
		// TRYB DZIENNY
		digitalWrite(cars_green, HIGH);  
		digitalWrite(people_red, HIGH); 
		delay(10000);
		digitalWrite(cars_green, LOW);
		digitalWrite(cars_yellow, HIGH);
		delay(2000);
		digitalWrite(cars_yellow, LOW);
		digitalWrite(cars_red, HIGH);
		delay(4000);
		digitalWrite(people_red, LOW);
		digitalWrite(people_green, HIGH);  
		delay(5000);
		for(int i=0; i<5; i++){
			digitalWrite(A0, HIGH); 
			delay(500);
			digitalWrite(A0, LOW);
			delay(500); 
		}
		digitalWrite(people_red, HIGH);
		delay(2000);
		digitalWrite(cars_red, LOW);
		digitalWrite(cars_yellow, HIGH);
		delay(1000);
		digitalWrite(cars_yellow, LOW);	
		digitalWrite(people_red, LOW);
	}
	else{
	 	digitalWrite(cars_yellow, HIGH);
		delay(500);
		digitalWrite(cars_yellow, LOW);
		delay(500);	
	}
}

void nightMode(){
	return 0;
}

void turnOnOffAll(int state){
	digitalWrite(cars_red, state);
	digitalWrite(cars_yellow, state);
	digitalWrite(cars_green, state);  
	digitalWrite(people_red, state);
	digitalWrite(people_green, state);
}