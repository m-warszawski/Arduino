#include <stdlib.h>

// Definicje pinów dla wejść, wyjśćs i segmentów wyświetlacza
const int inputPins[] = {0, 1, 2, 3, 4, 5, 6, 7};
const int hundredPins[] = {A15, A14, A13, A12, A11, A10, A9, A8};
const int decimalPins[] = {A7, A6, A5, A4, A3, A2, A1, A0};
const int unitsPins[] = {21, 20, 19, 18, 17, 16, 15, 14};
const int powersOfTwo[] = {128, 64, 32, 16, 8, 4, 2, 1};
const int decoderPins[] = {31, 33, 35};

void setup()
{
    // Konfiguracja pinów wejściowych z rezystorem pull-up
    for (int i = 0; i < 8; ++i)
    {
        pinMode(inputPins[i], INPUT_PULLUP);
    }

    // Konfiguracja pinów wejściowych z rezystorem pull-up
    for (int i = 0; i < 3; ++i)
    {
        pinMode(decoderPins[i], INPUT_PULLUP);
    }

    // Konfiguracja pinów wyjściowych dla wyświetlaczy
    for (int i = 0; i < 8; ++i)
    {
        pinMode(hundredPins[i], OUTPUT);
        digitalWrite(hundredPins[i], LOW);
        pinMode(decimalPins[i], OUTPUT);
        digitalWrite(decimalPins[i], LOW);
        pinMode(unitsPins[i], OUTPUT);
        digitalWrite(unitsPins[i], LOW);
    }
}

void loop()
{
    // Odczyt sygnałów sterujących
    int number = getDecoderPins();

    // Wyświetlanie odpowiednich danych
    switch (number)
    {
    // Kod Binarny -> Kod Dziesiętny
    case 0:;
        displayDecimalNumber(getBinaryCode());
        break;
    // Kod Gray'a -> Kod Dziesiętny
    case 1:
        displayDecimalNumber(getGrayCode());
        break;
    // Kod Binarny -> Kod Szesnastkowy
    case 2:
        displayHexNumber(convertDecimalToHexadecimal(getBinaryCode()));
        break;
    // Kod Gray'a -> Kod Szesnastkowy
    case 3:
        displayHexNumber(getGrayCode());
        break;
    // Kod Aikena -> Kod Dziesiętny
    case 4:
        displayDecimalNumber(getAikenCode());
        break;
    // Kod Aikena -> Kod Szesnastkowy
    case 5:
        displayHexNumber(getJohnsonCode());
        break;
    // Kod Johnsona -> Kod Dziesiętny
    case 6:
        displayDecimalNumber(getJohnsonCode());
        break;
    // Kod Johnsona -> Kod Szesnastkowy
    case 7:
        displayHexNumber(getJohnsonCode());
        break;
    default:
        break;
    }
}

// --> POBRANIE SYGNAŁÓW STERUJĄCYCH
int getDecoderPins()
{
    int result = 0;
    for (int i = 0; i < 3; ++i)
    {
        if (digitalRead(decoderPins[i]) == LOW)
        {
            result += powersOfTwo[i + 5];
        }
    }
    return result;
}

// --> POBIERANIE DANYCH WEJŚCIOWYCH W ODPOMIEDNIM KODZIE
int getBinaryCode()
{
    int decimalNumber = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (digitalRead(inputPins[i]) == LOW)
        {
            decimalNumber += powersOfTwo[i];
        }
    }
    return decimalNumber;
}

int getGrayCode()
{
    int gray[8];
    // Odczytanie kodu Gray'a
    for (int i = 0; i < 8; ++i)
    {
        if (digitalRead(inputPins[i]) == LOW)
        {
            gray[i] = 1;
        }
        else
        {
            gray[i] = 0;
        }
    }

    // Zmiana kodu Gray'a na binarny
    int binary[8];
    binary[0] = gray[0];
    for (int i = 1; i < 8; ++i)
    {
        if (binary[i - 1] == gray[i])
        {
            binary[i] = 0;
        }
        else
        {
            binary[i] = 1;
        }
    }

    // Zamiana kodu binarnego na liczbę dziesiętną
    return convertBinaryToDecimal(binary);
}

int getAikenCode()
{
    return 0;
}

int getJohnsonCode()
{
    return 0;
}

// --> ZAMIANA SYSTEMÓW LICZBOWYCH
int convertBinaryToDecimal(int binary[])
{
    int decimalNumber = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (binary[i] == 1)
        {
            decimalNumber += powersOfTwo[i];
        }
    }

    return decimalNumber;
}

char *convertDecimalToHexadecimal(int decimalNumber)
{
    int quotient;
    int i = 1, j, temp;
    char hexNumber[3];
    quotient = decimalNumber;

    while (quotient != 0)
    {
        temp = quotient % 16;
        if (temp < 10)
        {
            temp = temp + 48;
        }
        else
        {
            temp = temp + 55;
        }

        hexNumber[i++] = temp;
        quotient = quotient / 16;
    }

    char resultArray[3];
    resultArray[0] = hexNumber[2];
    resultArray[1] = hexNumber[1];
    resultArray[2] = hexNumber[0];

    return resultArray;
}

// --> WYŚWIETLANIE DANYCH NA WYŚWIETLACZU
void displayDecimalNumber(int decimalNumber)
{
    int hundreds = decimalNumber / 100;
    int decimals = (decimalNumber % 100) / 10;
    int units = decimalNumber % 10;

    // Mapa bitowa dla każdej cyfry
    const byte digitDecMap[] = {
        B00111111, // 0
        B00000110, // 1
        B01011011, // 2
        B01001111, // 3
        B01100110, // 4
        B01101101, // 5
        B01111101, // 6
        B00000111, // 7
        B01111111, // 8
        B01101111, // 9
    };

    // Wyświetlanie cyfry na odpowiednich wyświetlaczach
    for (int i = 0; i < 8; ++i)
    {
        digitalWrite(hundredPins[i], bitRead(digitDecMap[hundreds], i));
        digitalWrite(decimalPins[i], bitRead(digitDecMap[decimals], i));
        digitalWrite(unitsPins[i], bitRead(digitDecMap[units], i));
    }
}

void displayHexNumber(char *hexNumber)
{
    // Mapa bitowa dla każdej cyfry szesnastkowej
    const byte digitHexMap[] = {
        B01111110, // 0
        B00110000, // 1
        B01101101, // 2
        B01111001, // 3
        B00110011, // 4
        B01011011, // 5
        B01011111, // 6
        B01110000, // 7
        B01111111, // 8
        B01111011, // 9
        B01110111, // A
        B00011111, // B
        B01001110, // C
        B00111101, // D
        B01001111, // E
        B01000111  // F
    };

    // Wyświetlanie cyfry szesnastkowej na odpowiednich wyświetlaczach
    for (int i = 0; i < 3; ++i)
    {
        // Sprawdzenie, czy wartość jest poprawną cyfrą szesnastkową
        if ((hexNumber[i] >= '0' && hexNumber[i] <= '9') || (hexNumber[i] >= 'A' && hexNumber[i] <= 'F'))
        {
            // Konwersja cyfry szesnastkowej na odpowiadającą jej liczbę
            int index = (hexNumber[i] >= '0' && hexNumber[i] <= '9') ? (hexNumber[i] - '0') : (hexNumber[i] - 'A' + 10);

            // Wyświetlanie poszczególnych bitów cyfry szesnastkowej na wyświetlaczach
            digitalWrite(hundredPins[i], bitRead(digitHexMap[index], 6));
            digitalWrite(decimalPins[i], bitRead(digitHexMap[index], 5));
            digitalWrite(unitsPins[i], bitRead(digitHexMap[index], 4));
        }
        else
        {
            // Jeśli wartość nie jest poprawną cyfrą szesnastkową, wyłącz wyświetlacz
            digitalWrite(hundredPins[i], LOW);
            digitalWrite(decimalPins[i], LOW);
            digitalWrite(unitsPins[i], LOW);
        }
    }
}
