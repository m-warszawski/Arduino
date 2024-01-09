#include <stdlib.h>

// Definicje pinów dla mikrokontrolera i wyświetlacza siedmiosegmentowego
const int inputPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; 
const int hundretPins[] = {A15, A14, A13, A12, A11, A10, A9, A8};
const int decimalPins[] = {A7, A6, A5, A4, A3, A2, A1, A0};
const int unityPins[] = {21, 20, 19, 18, 17, 16, 15, 14};
const int numbers[] = {1, 2, 4, 8, 16, 32, 64, 128};

void setup() {
	// Inicjalizacja pinów wejściowych i wyjściowych
	for (int i = 0; i < 8; ++i) {
		pinMode(inputPins[i], INPUT_PULLUP);
	}

	for (int i = 0; i < 8; ++i) {
		pinMode(hundretPins[i], OUTPUT);
		digitalWrite(hundretPins[i], LOW);
		pinMode(decimalPins[i], OUTPUT);
		digitalWrite(decimalPins[i], LOW);
		pinMode(unityPins[i], OUTPUT);
		digitalWrite(unityPins[i], LOW);
	}
	
	// Sprawdzenie, czy suma indeksu jest parzysta i ustawienie kropki
	if((2+2+3+1+9+4)%2==0){
		digitalWrite(decimalPins[7], HIGH); 
	}
	else{
		digitalWrite(unityPins[7], HIGH); 
	}
}

void loop() {
	int number = getSignals();
	int lp = sizeof(numbers) / sizeof(numbers[0]);
	char digits[lp];
	
	// Podział liczby dziesiętnej na trzy cyfry w tablicy
	int tempNumber = number;
	for (int i = 0; i < lp; ++i) {
		digits[i] = tempNumber % 10;
		tempNumber /= 10;
	}	

	// Wyświetlanie cyfr na poszczególnych wyświetlaczach
	displayDigit(digits[0], unityPins);
	displayDigit(digits[1], decimalPins);
	displayDigit(digits[2], hundretPins);
}

void displayDigit(int digit, int pins[]) {
	// Mapowanie cyfr na reprezentację siedmiosegmentową
	switch (digit) {
		case 0:
			digitalWrite(pins[0], HIGH);
			digitalWrite(pins[1], HIGH);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], HIGH);
			digitalWrite(pins[4], HIGH);
			digitalWrite(pins[5], HIGH);
			digitalWrite(pins[6], LOW);
		break; 
		case 1:
			digitalWrite(pins[0], LOW);
			digitalWrite(pins[1], HIGH);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], LOW);
			digitalWrite(pins[4], LOW);
			digitalWrite(pins[5], LOW);
			digitalWrite(pins[6], LOW);
			break; 
		case 2:
			digitalWrite(pins[0], HIGH);
			digitalWrite(pins[1], HIGH);
			digitalWrite(pins[2], LOW);
			digitalWrite(pins[3], HIGH);
			digitalWrite(pins[4], HIGH);
			digitalWrite(pins[5], LOW);
			digitalWrite(pins[6], HIGH);
		break; 
		case 3:
			digitalWrite(pins[0], HIGH);
			digitalWrite(pins[1], HIGH);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], HIGH);
			digitalWrite(pins[4], LOW);
			digitalWrite(pins[5], LOW);
			digitalWrite(pins[6], HIGH);
		break; 
		case 4:
			digitalWrite(pins[0], LOW);
			digitalWrite(pins[1], HIGH);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], LOW);
			digitalWrite(pins[4], LOW);
			digitalWrite(pins[5], HIGH);
			digitalWrite(pins[6], HIGH);
		break; 
		case 5:
			digitalWrite(pins[0], HIGH);
			digitalWrite(pins[1], LOW);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], HIGH);
			digitalWrite(pins[4], LOW);
			digitalWrite(pins[5], HIGH);
			digitalWrite(pins[6], HIGH);
		break; 
		case 6:
			digitalWrite(pins[0], HIGH);
			digitalWrite(pins[1], LOW);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], HIGH);
			digitalWrite(pins[4], HIGH);
			digitalWrite(pins[5], HIGH);
			digitalWrite(pins[6], HIGH);
		break;
		case 7:
			digitalWrite(pins[0], HIGH);
			digitalWrite(pins[1], HIGH);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], LOW);
			digitalWrite(pins[4], LOW);
			digitalWrite(pins[5], LOW);
			digitalWrite(pins[6], LOW);
		break;
		case 8:
			digitalWrite(pins[0], HIGH);
			digitalWrite(pins[1], HIGH);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], HIGH);
			digitalWrite(pins[4], HIGH);
			digitalWrite(pins[5], HIGH);
			digitalWrite(pins[6], HIGH);
		break;
		case 9:
			digitalWrite(pins[0], HIGH);
			digitalWrite(pins[1], HIGH);
			digitalWrite(pins[2], HIGH);
			digitalWrite(pins[3], HIGH);
			digitalWrite(pins[4], LOW);
			digitalWrite(pins[5], HIGH);
			digitalWrite(pins[6], HIGH);
		break;
	}
}

int getSignals() {
	// Odczytywanie sygnałów z pinów wejściowych i konwersja na liczbę
	int result = 0;
	for (int i = 0; i < 8; ++i) {
		if (digitalRead(inputPins[i]) == LOW) {
			result += numbers[i];
		}
	}
	return result;
}

