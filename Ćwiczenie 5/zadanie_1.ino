const int secondServoPin = 5;
const int minuteServoPin = 6;
const int hourServoPin = 7;

const int buzzerPin = 39;

const long interval = 100; 

int seconds = 0;
int minutes = 0;
int hours = 0;

void setup() {
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
}

void rotateServo(int servoPin, int value, int range) {
  int angle = map(value, 0, range - 1, 0, 180);
  int pulseWidth = map(angle, 0, 180, 800, 2000);

  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
  delay(10);
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
