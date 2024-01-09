#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 3, d5 = 1, d6 = 9, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const float shuntResistance = 100.0; // Wartość rezystora shunt w ohmach

void setup() {
  // Konfiguracja LCD jako 16 kolumn na 2 wiersze
  lcd.begin(16, 2);
}

void loop() {
  // Pobranie wartości napięć z pinów analogowych
  int voltageValue0 = analogRead(A0);
  int voltageValue1 = analogRead(A7);

  // Obliczenie różnicy napięć
  int subtractionValue = voltageValue0 - voltageValue1;

  // Obliczenie prądu zgodnie ze wzorem podziału napięcia
  float current = (subtractionValue * 0.00488) / shuntResistance;

  // Wyświetlenie wartości prądu na monitorze szeregowym
  Serial.print("Current value: ");
  Serial.print(current);
  Serial.println(" A");

  // Wyświetlenie wartości prądu na LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current value=");
  lcd.setCursor(0, 1);
  lcd.print(current, 2); // Wyświetlenie z dwoma miejscami po przecinku
  lcd.print("A");

  delay(1000);
}
