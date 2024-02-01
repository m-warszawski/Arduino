//Import bibliotek
#include "LedControl.h"
#include "Keypad.h"

// Konfiguracja pinów dla matrycy LED i klawiatury
const int data_pin = 20;
const int clock_pin = 19;
const int CS_pin = 21;
const int num_matrices = 4;

LedControl lc = LedControl(data_pin, clock_pin, CS_pin, num_matrices);

// Konfiguracja klawiatury
char keys[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

byte row_pins[4] = {A9, A11, A13, A15};
byte col_pins[3] = {A7, A6, A5};

Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, 4, 3);

// Definicje macierzy dla poszczególnych cyfr
int zero[8][3] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
};

int one[8][3] = {
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
};

int two[8][3] = {
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
  {1, 1, 1},
  {1, 0, 0},
  {1, 0, 0},
  {1, 0, 0},
  {1, 1, 1},
};

int three[8][3] = {
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {1, 1, 1},
};

int four[8][3] = {
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
};

int five[8][3] = {
  {1, 1, 1},
  {1, 0, 0},
  {1, 0, 0},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {1, 1, 1},
};

int six[8][3] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 0},
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
};

int seven[8][3] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
};

int eight[8][3] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
};

int nine[8][3] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {1, 1, 1},
};

int colon[8][2] = {
  {0, 0},
  {1, 1},
  {1, 1},
  {0, 0},
  {0, 0},
  {1, 1},
  {1, 1},
  {0, 0},
};

// Zmienne do śledzenia czasu
unsigned long previous_millis = 0;
const long interval = 10;
int seconds = 0;
int minutes = 0;
int hours = 0;

// Funkcja ustawień
void setup()
{
  // Inicjalizacja matrycy LED
  for (int i = 0; i < num_matrices; i++)
  {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
  }
}

// Funkcja mapująca cyfrę na jej wzorzec wyświetlania
int (*digitToDisplay(int digit))[3]
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

// Zmienne trybu edycji
bool edit_mode = false;
int edit = 0;

// Główna pętla
void loop()
{
  unsigned long current_millis = millis();
  char key = keypad.getKey();
  // Wejście w tryb edycji po naciśnięciu '#'
  if (key == '#')
  {
    edit_mode = true;
    edit++;
  }
  // Wyjście z trybu edycji po naciśnięciu '*'
  if (key == '*')
  {
    edit_mode = false;
    edit = 0;
  }
  // Aktualizacja czasu w trybie nieedycji
  if (edit_mode == false && current_millis - previous_millis >= interval)
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

    displayOnMatrix(0, digitToDisplay(seconds % 10), 5, 7);
    displayOnMatrix(0, digitToDisplay(seconds / 10), 0, 2);
    displayOnMatrix(1, digitToDisplay(minutes % 10), 1, 3);
    displayOnMatrix(2, digitToDisplay(minutes / 10), 4, 6);
    displayOnMatrix(3, digitToDisplay(hours % 10), 5, 7);
    displayOnMatrix(3, digitToDisplay(hours / 10), 0, 2);
    displayColon(1, 5, 6);
    displayColon(2, 1, 2);
  }

  // Logika trybu edycji
  if (edit_mode == true)
  {
    // Wyświetlanie jedności sekund
    if (edit == 1)
    {
      if (key >= '0' && key <= '9')
      {
        seconds = (seconds / 10) * 10 + (key - '0');
      }
      clearDisplayColumn(0, 5, 7);
      delay(10);
      displayOnMatrix(0, digitToDisplay(seconds % 10), 5, 7);
      delay(10);
    }
    // Wyświetlanie dziesiątek sekund
    if (edit == 2)
    {
      if (key >= '0' && key <= '5')
      {
        int newTens = (key - '0') * 10;
        seconds = newTens + (seconds % 10);
      }
      clearDisplayColumn(0, 0, 2);
      delay(10);
      displayOnMatrix(0, digitToDisplay(seconds / 10), 0, 2);
      delay(10);
    }
    // Wyświetlanie jedności minut
    if (edit == 3)
    {
      if (key >= '0' && key <= '9')
      {
        minutes = (minutes / 10) * 10 + (key - '0');
      }
      clearDisplayColumn(1, 1, 3);
      delay(10);
      displayOnMatrix(1, digitToDisplay(minutes % 10), 1, 3);
      delay(10);
    }
    // Wyświetlanie dziesiątek minut
    if (edit == 4)
    {
      if (key >= '0' && key <= '5')
      {
        int newTens = (key - '0') * 10;
        minutes = newTens + (minutes % 10);
      }
      clearDisplayColumn(2, 4, 6);
      delay(10);
      displayOnMatrix(2, digitToDisplay(minutes / 10), 4, 6);
      delay(10);
    }
    // Wyświetlanie jedności godzin
    if (edit == 5)
    {
      if (hours <= 19 && key >= '0' && key <= '9')
      {
        hours = (hours / 10) * 10 + (key - '0');
      }
      if (hours >= 20 && key >= '0' && key <= '3')
      {
        hours = (hours / 10) * 10 + (key - '0');
      }
      clearDisplayColumn(3, 5, 7);
      delay(10);
      displayOnMatrix(3, digitToDisplay(hours % 10), 5, 7);
      delay(10);
    }
    // Wyświetlanie dziesiątek godzin
    if (edit == 6)
    {
      if (hours % 10 >= 5 && key >= '0' && key <= '1')
      {
        int newTens = (key - '0') * 10;
        hours = newTens + (hours % 10);
      }
      if (hours % 10 <= 4 && key >= '0' && key <= '2')
      {
        int newTens = (key - '0') * 10;
        hours = newTens + (hours % 10);
      }
      clearDisplayColumn(3, 0, 2);
      delay(10);
      displayOnMatrix(3, digitToDisplay(hours / 10), 0, 2);
      delay(10);
    }
    if (edit == 7)
    {
      edit = 1;
    }
  }
}

// Funkcja do wyświetlania wzorca cyfry na określonej matrycy i zakresie kolumn
void displayOnMatrix(int matrixNum, int pattern[8][3], int start_col, int end_col)
{
  for (int row = 0; row < 8; row++)
  {
    for (int col = start_col; col <= end_col; col++)
    {
      lc.setLed(matrixNum, row, col, pattern[row][col - start_col]);
    }
  }
}

// Funkcja do wyświetlania dwukropka na określonej matrycy i zakresie kolumn
void displayColon(int matrixNum, int start_col, int end_col)
{
  for (int row = 0; row < 8; row++)
  {
    for (int col = start_col; col <= end_col; col++)
    {
      lc.setLed(matrixNum, row, col, colon[row][col - start_col]);
    }
  }
}

// Funkcja do wyczyszczenia konkretnej kolumny na matrycy
void clearDisplayColumn(int matrixNum, int start_col, int end_col)
{
  for (int row = 0; row < 8; row++)
  {
    for (int col = start_col; col <= end_col; col++)
    {
      lc.setLed(matrixNum, row, col, 0);
    }
  }
}
