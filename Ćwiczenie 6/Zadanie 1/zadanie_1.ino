// Definicje dla liczby wierszy i kolumn w macierzy LED
const int number_of_rows = 8;
const int number_of_cols = 33;

// Definicje pinów dla wierszy i kolumn
const int row_pins[number_of_rows] = {0, 1, 2, 3, 4, 5, 6, 7};
const int col_pins[number_of_cols] = {14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46};

// Definicje macierzy dla poszczególnych cyfr
int zero[8][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1},
};

int one[8][4] = {
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
};

int two[8][4] = {
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {1, 1, 1, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1},
};

int three[8][4] = {
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {1, 1, 1, 1},
};

int four[8][4] = {
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
};

int five[9][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {1, 1, 1, 0},
};

int six[8][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 0},
};

int seven[8][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
};

int eight[8][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1},
};

int nine[8][4] = {
    {1, 1, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {1, 1, 1, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {0, 0, 0, 1},
    {1, 1, 1, 1},
};

int colon[8][1] = {
    {0},
    {0},
    {1},
    {0},
    {0},
    {1},
    {0},
    {0},
};

// Zmienne do śledzenia czasu
unsigned long previous_millis = 0;
const long interval = 1000; // Prędkość w milisekundach
int seconds = 0;
int minutes = 0;
int hours = 0;

void setup()
{
  // Inicjalizacja pinów w trybie OUTPUT
  for (int i = 0; i < number_of_rows; i++)
  {
    pinMode(row_pins[i], OUTPUT);
    digitalWrite(row_pins[i], LOW);
  }
  for (int i = 0; i < number_of_cols; i++)
  {
    pinMode(col_pins[i], OUTPUT);
    digitalWrite(col_pins[i], HIGH);
  }
}

void loop()
{
  // Aktualny czas w milisekundach
  unsigned long current_millis = millis();

  // Aktualizacja czasu co określony interwał
  if (current_millis - previous_millis >= interval)
  {
    previous_millis = current_millis;
    seconds = (seconds + 1) % 60;
    if (seconds == 0)
    {
      minutes = (minutes + 1) % 60;

      if (minutes == 0)
      {
        hours = (hours + 1) % 24;
      }
    }
  }

  displayTimeOnMatrix(hours, minutes, seconds);
}

// Funkcja do ustawiania konkretnej wiersz w stanie HIGH, pozostałe w LOW
void selectRow(int row)
{
  for (int i = 0; i < number_of_rows; i++)
  {
    digitalWrite(row_pins[i], (i == row) ? HIGH : LOW);
  }
}

// Funkcja do ustawiania konkretnej kolumny w stanie LOW, pozostałe w HIGH
void selectColumn(int col)
{
  for (int i = 0; i < number_of_cols; i++)
  {
    digitalWrite(col_pins[i], (i == col) ? LOW : HIGH);
  }
}

// Funkcje do ustawiania stanu segmentów dla poszczególnych
void setHourTens(int col, int state)
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(col_pins[i], (i == col) ? !state : HIGH);
  }
  delayMicroseconds(1000);
}

void setHourOnes(int col, int state)
{
  for (int i = 5; i < 9; i++)
  {
    digitalWrite(col_pins[i], (i - 5 == col) ? !state : HIGH);
  }
  delayMicroseconds(1000);
}

void setMinuteTens(int col, int state)
{
  for (int i = 12; i < 16; i++)
  {
    digitalWrite(col_pins[i], (i - 12 == col) ? !state : HIGH);
  }
  delayMicroseconds(1000);
}

void setMinutesOnes(int col, int state)
{
  for (int i = 17; i < 21; i++)
  {
    digitalWrite(col_pins[i], (i - 17 == col) ? !state : HIGH);
  }
  delayMicroseconds(1000);
}

void setSecondTens(int col, int state)
{
  for (int i = 24; i < 28; i++)
  {
    digitalWrite(col_pins[i], (i - 24 == col) ? !state : HIGH);
  }
 delayMicroseconds(1000);
}

void setSecondOnes(int col, int state)
{
  for (int i = 29; i < 33; i++)
  {
    digitalWrite(col_pins[i], (i - 29 == col) ? !state : HIGH);
  }
  delayMicroseconds(1000);
}

// Funkcja mapująca cyfrę na jej reprezentację w postaci macierzy
int (*digitToDisplay(int digit))[4]
{
  switch (digit)
  {
  case 0:
    return zero;
  case 1:
    return one;
  case 2:
    return two;
  case 3:
    return three;
  case 4:
    return four;
  case 5:
    return five;
  case 6:
    return six;
  case 7:
    return seven;
  case 8:
    return eight;
  case 9:
    return nine;
  default:
    return zero;
  }
}

// Funkcja do wyświetlania czasu na macierzy LED
void displayTimeOnMatrix(int hours, int minutes, int seconds)
{
  int(*digit)[4];
  // Wyświetlanie dziesiątek godzin
  if (hours > 9)
  {
    digit = digitToDisplay(hours / 10);
    for (int i = 0; i < 8; i++)
    {
      selectRow(i);
      for (int j = 0; j < 4; j++)
      {
        setHourTens(j, digit[i][j]);
      }
    }
  }

  // Wyświetlanie jedności godzin
  if (hours > 0)
  {
    digit = digitToDisplay(hours % 10);
    for (int i = 0; i < 8; i++)
    {
      selectRow(i);
      for (int j = 5; j < 9; j++)
      {
        setHourOnes(j - 5, digit[i][j - 5]);
      }
    }
  }

  // Wyświetlanie dziesiątek minut
  if (minutes > 9 || hours > 0)
  {
    digit = digitToDisplay(minutes / 10);
    for (int i = 0; i < 8; i++)
    {
      selectRow(i);
      for (int j = 12; j < 16; j++)
      {
        setMinuteTens(j - 12, digit[i][j - 12]);
      }
    }
  }

  // Wyświetlanie jedności minut
  if (minutes > 0 || hours > 0)
  {
    digit = digitToDisplay(minutes % 10);
    for (int i = 0; i < 8; i++)
    {
      selectRow(i);
      for (int j = 17; j < 21; j++)
      {
        setMinutesOnes(j - 17, digit[i][j - 17]);
      }
    }
  }

  // Wyświetlanie dziesiątek sekund
  if (seconds > 9 || minutes > 0 || hours > 0)
  {
    digit = digitToDisplay(seconds / 10);
    for (int i = 0; i < 8; i++)
    {
      selectRow(i);
      for (int j = 24; j < 28; j++)
      {
        setSecondTens(j - 24, digit[i][j - 24]);
      }
    }
  }

  // Wyświetlanie jedności sekund
  digit = digitToDisplay(seconds % 10);
  for (int i = 0; i < 8; i++)
  {
    selectRow(i);
    for (int j = 29; j < 33; j++)
    {
      setSecondOnes(j - 29, digit[i][j - 29]);
    }
  }
}
