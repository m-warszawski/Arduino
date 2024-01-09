const int secondServoPin = 5;
const int minuteServoPin = 6;
const int hourServoPin = 7;

const int secondPins[] = {A8, A9, A10};
const int minutePins[] = {A5, A6, A7};
const int hourPins[] = {A0, A1, A2};

const int buzzerPin = 39;

const long interval = 100; 

int seconds = 0;
int minutes = 0;
int hours = 0;

void setup() {
  for(int i = 0; i < 3; i++) {
    pinMode(secondPins[i], OUTPUT);
    pinMode(minutePins[i], OUTPUT);
    pinMode(hourPins[i], OUTPUT);
  }

  pinMode(buzzerPin, OUTPUT);
}

void loop() {
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
    if (minutes == 60)
    {
        ++hours;
        minutes = 0;
    }
    if (hours == 11)
    {
        hours = 0;
    }

    rotateServo(secondServoPin, seconds, 60);
    rotateServo(minuteServoPin, minutes, 60);
    rotateServo(hourServoPin, hours, 12);

    displayTime(hours, hourPins[0], hourPins[1], hourPins[2], 12);
    displayTime(minutes, minutePins[0], minutePins[1], minutePins[2], 60);
    displayTime(seconds, secondPins[0], secondPins[1], secondPins[2], 60);
 
}

void rotateServo(int servoPin, int value, int range) {
  int angle = map(value, 0, range - 1, 0, 180);
  int pulseWidth = map(angle, 0, 180, 800, 2000);

  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
}

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
