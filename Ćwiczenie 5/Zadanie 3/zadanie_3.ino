// Definicje pinów dla serwomechanizmów
const int secondServoPin = 5;
const int minuteServoPin = 6;
const int hourServoPin = 7;

// Definicje pinów dla wyświetlaczy 7-segmentowych
// DS  ST_CP  SH_CP
const int secondPins[] = {A8, A9, A10};
const int minutePins[] = {A5, A6, A7};
const int hourPins[] = {A0, A1, A2};

// Definicje pinów dla silników krokowych
// A+  B+  A-  B-
const int secondStepperPins[] = {47, 49, 51, 53};
const int minuteStepperPins[] = {39, 41, 43, 45};
const int hourStepperPins[] = {31, 33, 35, 37};

// Pin dla buzzer'a
const int buzzerPin = 10;

// Interwał między krokami w milisekundach
const long interval = 100;

// Zmienne przechowujące aktualny czas
int seconds = 0;
int minutes = 0;
int hours = 0;

void setup()
{
    // Konfiguracja pinów dla wyświetlaczy 7-segmentowych
    for (int i = 0; i < 3; i++)
    {
        pinMode(secondPins[i], OUTPUT);
        pinMode(minutePins[i], OUTPUT);
        pinMode(hourPins[i], OUTPUT);
    }

    // Konfiguracja pinów dla silników krokowych
    for (int j = 0; j < 4; j++)
    {
        pinMode(secondStepperPins[j], OUTPUT);
        pinMode(minuteStepperPins[j], OUTPUT);
        pinMode(hourStepperPins[j], OUTPUT);
    }

    // Konfiguracja pinu dla buzzer'a
    pinMode(buzzerPin, OUTPUT);
}

void loop()
{
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

    // Wyświetlanie czasu na wyświetlaczach 7-segmentowych
    displayTime(hours, hourPins[0], hourPins[1], hourPins[2], 12);
    displayTime(minutes, minutePins[0], minutePins[1], minutePins[2], 60);
    displayTime(seconds, secondPins[0], secondPins[1], secondPins[2], 60);

    // Obracanie silników krokowych
    rotateStepper(secondStepperPins, seconds);
    rotateStepper(minuteStepperPins, minutes);
    rotateStepper(hourStepperPins, hours);
}

// Funkcja obracająca serwomechanizm
void rotateServo(int servoPin, int value, int range)
{
    int angle = map(value, 0, range - 1, 0, 180);
    int pulseWidth = map(angle, 0, 180, 900, 2000);

    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(servoPin, LOW);
}

// Funkcja wyświetlająca czas na wyświetlaczach 7-segmentowych
void displayTime(int value, int dsPin, int stcpPin, int shcpPin, int range)
{
    int tens = value / 10;
    int ones = value % 10;

    char tensData = mapToSegments(tens);
    char onesData = mapToSegments(ones);

    digitalWrite(stcpPin, LOW);
    shiftOut(dsPin, shcpPin, MSBFIRST, onesData);
    shiftOut(dsPin, shcpPin, MSBFIRST, tensData);
    digitalWrite(stcpPin, HIGH);
}

// Funkcja obracająca silniki krokowe
void rotateStepper(int stepperPins[], int part)
{
   switch (part % 4)
    {
    case 0:
        digitalWrite(stepperPins[3], HIGH);
        digitalWrite(stepperPins[3], LOW);
        break;
    case 1:
        digitalWrite(stepperPins[2], HIGH);
        digitalWrite(stepperPins[2], LOW);
        break;
    case 2:
        digitalWrite(stepperPins[1], HIGH);
        digitalWrite(stepperPins[1], LOW);
        break;
    case 3:
        digitalWrite(stepperPins[0], HIGH);
        digitalWrite(stepperPins[0], LOW);
        break;
    default:
        break;
    }
}

// Mapowanie cyfr na segmenty dla wyświetlaczy 7-segmentowych
unsigned char mapToSegments(int digit)
{
    switch (digit)
    {
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

// Funkcja odtwarzająca alarm
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
