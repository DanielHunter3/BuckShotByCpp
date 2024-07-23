#pragma once

#include <string>
#include <iostream>
#include <stdio.h>

#include "Shotgun.h"
#include "Player.h"
#include "Winda.h"
#include "Constant.h"

/// @brief Есть ли строка в массиве строк
/// @tparam N Кол-во элементов в массиве строк
/// @param array массив со строками
/// @param str строка
/// @return bool
template<size_t N>
bool in_array(const std::string(&array)[N], std::string str)
{
    for (auto& i : array) if (i == str) return true;
    return false;
}

/// @brief Есть ли символ в строке
/// @param a строка
/// @param b символ
/// @return bool
bool in_array(std::string a, char b)
{
    for (auto& i : a) if (i == b) return true;
    return false;
}

template<typename T>
bool in_vector(std::vector<T> vec, T var)
{
    for (T &i: vec) if (i == var) return true;
    return false;
}

/// @brief Подходит имя или нет
/// @param name имя игрока
/// @param num порядковый номер игрока
void check(std::string name, size_t num)
{
    const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // * Алфавит
	//int target = 0;
    bool letters = false; // * Наличие букв алфавита

    printf("Enter a name of %zd player: ", num);
    while (true) {
        // ++target;
        // if (target == 1) printf("Enter a name of %zd player: ", num);
        std::cin >> name;

        for (auto& i : ALPHABET)
        {
            if (in_array(name, i))
            {
                letters = true; // * Присутствуют буквы алфавита
                break;          // * Ломаем цикл
            }
        }

        if (name.size() <= 3 || !letters) std::cout << "Again: "; // * Если имя меньше 3 или нет букв, то повторить цикл
        else break;
    }
}
