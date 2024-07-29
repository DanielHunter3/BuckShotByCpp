#pragma once

#include <string>
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>

#include "Shotgun.h"
#include "Player.h"
#include "Winda.h"
#include "Constant.h"

// /// @brief Есть ли строка в массиве строк
// /// @tparam N Кол-во элементов в массиве строк
// /// @param array массив со строками
// /// @param str строка
// /// @return bool
// template<size_t N>
// bool in_array(const std::string(&array)[N], std::string str)
// {
//     for (auto& i : array) if (i == str) return true;
//     return false;
// }

// /// @brief Есть ли символ в строке
// /// @param a строка
// /// @param b символ
// /// @return bool
// bool in_array(std::string a, char b)
// {
//     for (auto& i : a) if (i == b) return true;
//     return false;
// }

// template<typename T>
// bool in_vector(std::vector<T> vec, T var)
// {
//     for (T &i: vec) if (i == var) return true;
//     return false;
// }

template<typename Container, typename T>
bool in_container(const Container& container, const T& value)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

/// @brief Подходит имя или нет
/// @param name имя игрока
/// @param num порядковый номер игрока
void check(std::string& name, size_t num)
{
    const std::set<char> ALPHABET = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    printf("Enter a name of %zd player: ", num);
    while (!(std::cin >> name) || name.size() <= 3 || !in_container(ALPHABET, name[0])) {
        std::cout << "Invalid name. Enter a name of " << num << " player (at least 4 characters, starting with a letter): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


// void check(std::string name, size_t num)
// {
//     const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"; // * Алфавит
// 	//int target = 0;
//     bool letters = false; // * Наличие букв алфавита

//     printf("Enter a name of %zd player: ", num);
//     while (true) {
//         // ++target;
//         // if (target == 1) printf("Enter a name of %zd player: ", num);
//         std::cin >> name;

//         for (auto& i : ALPHABET)
//         {
//             if (in_array(name, i))
//             {
//                 letters = true; // * Присутствуют буквы алфавита
//                 break;          // * Ломаем цикл
//             }
//         }

//         if (name.size() <= 3 || !letters) std::cout << "Again: "; // * Если имя меньше 3 или нет букв, то повторить цикл
//         else break;
//     }
// }
