#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 3, d5 = 1, d6 = 9, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int outputPins[] = {A1, A2, A3, A4, A5};
int potencjometr = A7;

void setup()
{
	pinMode(potencjometr, INPUT);
	for (int i = 0; i < 5; i++)
	{
		pinMode(outputPins[i], OUTPUT);
		digitalWrite(outputPins[i], HIGH);
	}
	lcd.begin(16, 2);
}

void loop()
{
	float voltage = 0.0;
	int check = 0;
	bool state = false;

	digitalWrite(A5, LOW);
	delay(50);
	if (state == false && (analogRead(potencjometr) > 818.4))
	{
		lcd.print(analogRead(potencjometr) / 204.6 * 200);
		state = true;
	}
	digitalWrite(A5, HIGH);

	digitalWrite(A4, LOW);
	delay(20);
	if (state == false && (analogRead(potencjometr) > 767.25))
	{
		lcd.print(analogRead(potencjometr) / 204.6 * 160);
		state = true;
	}
	digitalWrite(A4, HIGH);

	digitalWrite(A3, LOW);
	delay(20);

	if (state == false && (analogRead(potencjometr) > 682))
	{
		lcd.print(analogRead(potencjometr) / 204.6 * 120);
		state = true;
	}

	digitalWrite(A3, HIGH);

	digitalWrite(A2, LOW);
	delay(20);
	if (state == false && (analogRead(potencjometr) > 511.5))
	{
		lcd.print(analogRead(potencjometr) / 204.6 * 80);
		state = true;
	}
	digitalWrite(A2, HIGH);

	digitalWrite(A1, LOW);
	delay(20);
	if (state == false && (analogRead(potencjometr) > 0))
	{
		lcd.print(analogRead(potencjometr) / 204.6 * 40);
		state = true;
	}
	digitalWrite(A1, HIGH);

	delay(1000);
	lcd.clear();
}