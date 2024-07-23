#pragma once

#include <iostream>
#include <windows.h>

using namespace std;

short length_matrix = 100; // * Длина матрицы
/// @brief Изменение длины матрицы
/// @param n длина матрицы
void re_length_matrix(short n) { length_matrix = abs(n); }

enum Colors {
    Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray,
    DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

template<Colors txt = LightGray, Colors bg = Black>
std::ostream& color(ostream& text) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | txt));
    return text;
}

int Modulus(int iN, int iMod) {
    int iQ = (iN / iMod);
    return iN - (iQ * iMod);
}

char GetChar(int iGenerator, char cBase, int iRange) {
    return (cBase + Modulus(iGenerator, iRange));
}

/// @brief Матрица
void matrix() {
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);

    char caRow[80];
    int j = 7;
    int k = 2;
    int l = 5;
    int m = 1;
    int z = 0;
    while (z != length_matrix) {
        int i = 0;
        while (i < 80) {
            if (caRow[i] != ' ') {
                caRow[i] = GetChar(j + i * i, 33, 30);
                if (((i * i + k) % 71) == 0) {
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else {
                    SetConsoleTextAttribute(hConsole, 2);
                }
            }
            std::cout << caRow[i];
            ++i;
            SetConsoleTextAttribute(hConsole, 2);
        }
        j = (j + 31);
        k = (k + 17);
        l = (l + 47);
        m = (m + 67);
        caRow[Modulus(j, 80)] = '-';
        caRow[Modulus(k, 80)] = ' ';
        caRow[Modulus(l, 80)] = '-';
        caRow[Modulus(m, 80)] = ' ';

        Sleep(10);
        ++z;
    }

    system("cls");
}
