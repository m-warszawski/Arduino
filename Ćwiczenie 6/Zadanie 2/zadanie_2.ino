#include <Arduino.h>
#include <Keypad.h>

// Definicje dla liczby wierszy i kolumn w macierzy LED
const int number_of_rows = 8;
const int number_of_cols = 33;

// Definicje pinów dla wierszy i kolumn
const int row_pins[number_of_rows] = {0, 1, 2, 3, 4, 5, 6, 7};
const int col_pins[number_of_cols] = {14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46};

// Definicje dla macierzy LED
int led_matrix[16][33];

// Definicje dla klawiatury
const byte ROW_NUM = 3;
const byte COLUMN_NUM = 3;

char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}};

byte pin_rows[ROW_NUM] = {9, 8, 7};
byte pin_column[COLUMN_NUM] = {6, 5, 4};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void setup()
{
  for (int i = 0; i < number_of_rows; i++)
  {
    pinMode(row_pins[i], OUTPUT);
    digitalWrite(row_pins[i], HIGH);
  }

  for (int i = 0; i < number_of_cols; i++)
  {
    pinMode(col_pins[i], OUTPUT);
    digitalWrite(col_pins[i], LOW);
  }

  for (int i = 0; i < number_of_rows; i++)
  {
    for (int j = 0; j < number_of_cols; j++)
    {
      led_matrix[i][j] = 1;
    }
  }
  led_matrix[1][1] = 0;

  keypad.setDebounceTime(10);
}

void loop()
{
  char key = keypad.getKey();

  // Tu dodaj kod obsługi klawiatury, np. poruszanie elementem w grze Tetris

  // Tu dodaj kod aktualizacji macierzy LED na podstawie logiki gry Tetris

  // Wyświetlenie macierzy LED
  for (int i = 0; i < number_of_rows; i++)
  {
    digitalWrite(row_pins[i], LOW);

    for (int j = 0; j < number_of_cols; j++)
    {
      digitalWrite(col_pins[j], led_matrix[i][j]);
    }

    digitalWrite(row_pins[i], HIGH);
  }
}
