#include <stdlib.h>

// Definicje pinów dla wejść, wyjść i segmentów wyświetlacza
const int inputPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; 
const int hundretPins[] = {A15, A14, A13, A12, A11, A10, A9, A8};
const int decimalPins[] = {A7, A6, A5, A4, A3, A2, A1, A0};
const int unityPins[] = {21, 20, 19, 18, 17, 16, 15, 14};
const int numbers[] = {128, 64, 32, 16, 8, 4, 2, 1};

void setup() {
	// Konfiguracja pinów wejściowych z rezystorem pull-up
	for (int i = 0; i < 8; ++i) {	
		pinMode(inputPins[i], INPUT_PULLUP);
	}
	
	// Konfiguracja pinów wyjściowych dla setek, dziesiątek i jedności
	for (int i = 0; i < 8; ++i) {
		pinMode(hundretPins[i], OUTPUT);
		digitalWrite(hundretPins[i], LOW);
		pinMode(decimalPins[i], OUTPUT);
		digitalWrite(decimalPins[i], LOW);
		pinMode(unityPins[i], OUTPUT);
		digitalWrite(unityPins[i], LOW);
	}
}

void loop() {
	// Odczyt sygnałów wejściowych
	int number = getSignals();
	int lp = sizeof(numbers) / sizeof(numbers[0]);
	char digits[lp];
	
	// Rozdzielenie liczby na poszczególne cyfry
	int tempNumber = number;
	for (int i = 0; i < lp; ++i) {
		digits[i] = tempNumber % 10;
		tempNumber /= 10;
	}

	// Wybór, który segment wyświetlacza będzie miał włączoną kropkę
	if((2+2+3+1+9+4)%2==0){
		displayDigit(digits[0], unityPins, false);
		displayDigit(digits[1], decimalPins, true);
	}
	else{
		displayDigit(digits[0], unityPins, true);
		displayDigit(digits[1], decimalPins, false);
	}
	displayDigit(digits[2], hundretPins, false);
}

void displayDigit(int digit, int pins[], bool showDot) {
	// Mapa bitowa dla każdej cyfry
	const byte digitMap[] = {
		B00111111, // 0
		B00000110, // 1
		B01011011, // 2
		B01001111, // 3
		B01100110, // 4
		B01101101, // 5
		B01111101, // 6
		B00000111, // 7
		B01111111, // 8
		B01101111 // 9
	};
	
	// Wyświetlanie cyfry na odpowiednich wyświetlaczach
	for (int i = 0; i < 8; ++i) {
		digitalWrite(pins[i], bitRead(digitMap[digit], i));
	}
	
	// Włączenie kropki dla dziesiątek, jeśli showDot jest true
	for (int i = 0; i < 8; ++i) {
		if (i == 7 && showDot) {
			digitalWrite(pins[i], HIGH); 
		} else {
			digitalWrite(pins[i], bitRead(digitMap[digit], i));
		}
	}
}

// Odczyt sygnałów wejściowych i przekształcenie ich na liczbę
int getSignals() {
	int gray[8];
	int binary[8];
	int result = 0;
	
	// zczytanie kodu Gray'a
	for (int i = 0; i < 8; ++i) {
		if (digitalRead(inputPins[i]) == LOW) {
			gray[i] = 1;
		}
	}
	
	// zmiana gray'a na binarny
	binary[0] = gray[0];
	for (int i = 1; i < 8; ++i) {
		if (binary[i-1] == gray[i]){
			binary[i] = 0;
		}
		else{
			binary[i] = 1;
		}
	}
	
	// zamiana binarnego na dziesiętny
	for (int i = 0; i < 8; ++i) {
		if (binary[i] == 1) {
			result += numbers[i];
		}
	}
		
	return result;
}
