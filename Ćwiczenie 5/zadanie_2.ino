// Definicje pinów dla serwomechanizmów
const int secondServoPin = 5;
const int minuteServoPin = 6;
const int hourServoPin = 7;

// Definicje pinów dla wyświetlaczy 7-segmentowych
// DS  ST_CP  SH_CP
const int secondPins[] = {A8, A9, A10};
const int minutePins[] = {A5, A6, A7};
const int hourPins[] = {A0, A1, A2};

// Pin dla buzzer'a
const int buzzerPin = 10;

// Interwał między krokami w milisekundach
const long interval = 100;

// Zmienne przechowujące aktualny czas
int seconds = 0;
int minutes = 0;
int hours = 0;


void setup() {
  // Inicjalizacja pinów wyjściowych dla serwomechanizmów i brzęczyka
  for(int i = 0; i < 3; i++) {
    pinMode(secondPins[i], OUTPUT);
    pinMode(minutePins[i], OUTPUT);
    pinMode(hourPins[i], OUTPUT);
  }

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
    // Inkrementacja licznika sekund, obsługa minut i odtwarzanie alarmu
    if (seconds < 60)
    {
        ++seconds;
        delay(interval);
        if (seconds == 60)
        {
        ++minutes;
        seconds = 0;
        playAlarm();
        }
    }
    // Inkrementacja licznika godzin
    if (minutes == 60)
    {
        ++hours;
        minutes = 0;
    }
    // Resetowanie licznika godzin po osiągnięciu 11
    if (hours == 11)
    {
        hours = 0;
    }

    // Obrót serwomechanizmów wskazówek
    rotateServo(secondServoPin, seconds, 60);
    rotateServo(minuteServoPin, minutes, 60);
    rotateServo(hourServoPin, hours, 12);

    // Wyświetlanie czasu na wyświetlaczach siedmiosegmentowych
    displayTime(hours, hourPins[0], hourPins[1], hourPins[2], 12);
    displayTime(minutes, minutePins[0], minutePins[1], minutePins[2], 60);
    displayTime(seconds, secondPins[0], secondPins[1], secondPins[2], 60);
}

// Funkcja do obracania serwomechanizmów
void rotateServo(int servoPin, int value, int range) {
  int angle = map(value, 0, range - 1, 0, 180);
  int pulseWidth = map(angle, 0, 180, 800, 2000);

  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
}

// Funkcja do wyświetlania czasu na wyświetlaczach siedmiosegmentowych
void displayTime(int value, int dsPin, int stcpPin, int shcpPin, int range) {
  int tens = value / 10;
  int ones = value % 10;

  char tensData = mapToSegments(tens);
  char onesData = mapToSegments(ones);

  digitalWrite(stcpPin, LOW);
  shiftOut(dsPin, shcpPin, MSBFIRST, onesData);
  shiftOut(dsPin, shcpPin, MSBFIRST, tensData);
  digitalWrite(stcpPin, HIGH);
}

// Funkcja mapująca cyfry na segmenty wyświetlacza siedmiosegmentowego
unsigned char mapToSegments(int digit) {
  switch (digit) {
    case 0: 
	return B00111111;
    case 1: 
	return B00000110;
    case 2: 
	return B01011011;
    case 3: 
	return B01001111;
    case 4: 
	return B01100110;
    case 5: 
	return B01101101;
    case 6: 
	return B01111101;
    case 7: 
	return B00000111;
    case 8: 
	return B01111111;
    case 9:
	return B01101111;
    default: 
	return 0;
  }
}

// Funkcja do odtwarzania alarmu
void playAlarm()
{
  for (int i = 0; i < 20; i++)
  {
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(1000);
  }
}
