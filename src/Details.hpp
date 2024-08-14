#pragma once

#include <iostream>
#include <algorithm>
#include <set>
#include <random>

template<typename Container, typename T>
bool in_container(const Container& container, const T& value)
{
    return std::find(container.begin(), container.end(), value) != container.end();
}

/// @brief Подходит имя или нет
/// @param name имя игрока
/// @param num порядковый номер игрока
void check(std::string& name)
{
    const std::set<char> ALPHABET = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    std::cout << "Enter a name of player: ";
    while (!(std::cin >> name) || name.size() <= 3 || !in_container(ALPHABET, name[0])) {
        std::cout << "Invalid name. Enter a name of player (at least 4 characters, starting with a letter): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void output_text(std::string text)
{
    for (auto &i: text)
    {
        std::cout << i;
        Sleep(100); //100
    }
}

int randint(int min = 0, int max = 1)
{
    std::random_device rnd;
	std::mt19937 gen(rnd());
	std::uniform_int_distribution<std::mt19937::result_type> dist(std::min(min, max), std::max(min, max));
    return dist(gen);
}