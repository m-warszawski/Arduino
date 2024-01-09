#include <LiquidCrystal.h>

// Pin, do którego podłączony jest potencjometr
const int potencjometr = A0;                          
// Piny podłączone do LCD      
const int rs = 12, en = 11, d4 = 3, d5 = 1, d6 = 9, d7 = 4; 
// Inicjalizacja obiektu LiquidCrystal
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                  

void setup()
{
    // Konfiguracja LCD jako 16 kolumn na 2 wiersze
    lcd.begin(16, 2); 
}

void loop()
{
    int wartosc = 0;
    // Odczyt wartości z potencjometru
    wartosc = analogRead(potencjometr);
    // Konwersja wartości na napięcie (w zakresie 0-5V)
    float volt = wartosc / 204.6;

    // Wyświetlenie napięcia na LCD
    lcd.print(volt);
    // Wydruk napięcia z jednostką
    lcd.print(" V"); 
    delay(1000); 
    // Wyczyszczenie ekran LCD   
    lcd.clear();     
}
