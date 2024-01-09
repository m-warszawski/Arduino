// Definicje pinów dla serwomechanizmów
const int secondServoPin = 5;
const int minuteServoPin = 6;
const int hourServoPin = 7;

// Definicja pinu dla buzzer'a
const int buzzerPin = 39;

// Interwał między krokami w milisekundach
const long interval = 100; 

// Zmienne przechowujące aktualny czas
int seconds = 0;
int minutes = 0;
int hours = 0;

void setup() {
  // Ustawienie pinu buzzer'a jako wyjście
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
    // Inkrementacja sekund i sprawdzenie warunku przejścia do kolejnej minuty
    if (seconds < 60)
    {
        ++seconds;
        delay(interval);
        if (seconds == 60)
        {
            ++minutes;
            seconds = 0;
            // Odtworzenie dźwięku alarmu na przejście do nowej minuty
            playAlarm();
        }
    }

    // Sprawdzenie warunku przejścia do kolejnej godziny
    if (minutes == 60)
    {
        ++hours;
        minutes = 0;
    }

    // Sprawdzenie warunku zresetowania godzin po 11
    if (hours == 11)
    {
        hours = 0;
    }

    // Aktualizacja pozycji serwomechanizmów zgodnie z czasem
    rotateServo(secondServoPin, seconds, 60);
    rotateServo(minuteServoPin, minutes, 60);
    rotateServo(hourServoPin, hours, 12);
}

// Funkcja obracająca serwomechanizm
void rotateServo(int servoPin, int value, int range) {
  // Mapowanie wartości czasu na kąt obrotu i szerokość impulsu PWM
  int angle = map(value, 0, range - 1, 0, 180);
  int pulseWidth = map(angle, 0, 180, 800, 2000);

  // Wysłanie impulsu do serwomechanizmu
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
  delay(10);
}

// Funkcja odtwarzająca alarm
void playAlarm()
{
  // Odtworzenie dźwięku alarmu przez zmianę stanu pinu buzzer'a
  for (int i = 0; i < 20; i++)
  {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(1000);
  }
}
