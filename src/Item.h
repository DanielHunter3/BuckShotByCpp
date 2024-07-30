#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <random>

// TODO: #include "Player.h"
// TODO: #include "Shotgun.h"

enum Objects { BEER, CIGARETTE, MAGNIFIER, KNIFE, HANDCUFFS };
class Items
{
private:
	// ! Указатель, очищается в деструкторе
	std::vector<Objects> *items = new std::vector<Objects>; // * Очередь объектов

public:
	/// @brief Перевести из числа в объект
	/// @param number номер объекта
	/// @return Objects
	Objects translatorToItem(size_t number)
	{
		std::map<size_t, Objects> translate
		{
			{1, Objects::MAGNIFIER},
			{2, Objects::CIGARETTE},
			{3, Objects::HANDCUFFS},
			{4, Objects::BEER},
			{5, Objects::KNIFE}
		};

		return translate[number];
	}

	/// @brief Перевести из строки в объект
	/// @param str строчное название объекта
	/// @return Objects
	Objects translatorToItem(std::string str)
	{
		std::map<std::string, Objects> translate
		{
			{"BEER", Objects::BEER},
			{"MAGNIFIER", Objects::MAGNIFIER},
			{"HANDCUFFS", Objects::HANDCUFFS},
			{"KNIFE", Objects::KNIFE},
			{"CIGARETTE", Objects::CIGARETTE}
		};

		return translate[str];
	}

	/// @brief Перевести из объекта в строку
	/// @param object объект в типе Objects
	/// @return std::string
	std::string translatorToString(Objects &object)
	{
		std::map<Objects, std::string> translate
		{
			{Objects::BEER, "BEER"},
			{Objects::MAGNIFIER, "MAGNIFIER"},
			{Objects::HANDCUFFS, "HANDCUFFS"},
			{Objects::KNIFE, "KNIFE"},
			{Objects::CIGARETTE, "CIGARETTE"}
		};

		return translate[object];
	}

	/// @brief Сгенерировать очередь объектов
	/// @param number кол-во объектов
	void generate(size_t number)
	{
		std::random_device rnd;
		std::mt19937 gen(rnd());
		std::uniform_int_distribution<> dist(1, 5);

		items->reserve(number);

		for (unsigned i = 0; i < number; ++i)
		{
			if (items->size() > 7) break;
            items->push_back(translatorToItem(dist(gen)));
		} 

		// for (unsigned i = 0; i < number; ++i)
		// {
		// 	if (items->size() > 7) break;
		// 	std::uniform_int_distribution<> *dist = new std::uniform_int_distribution<>(1, 5);
		// 	items->push_back(translatorToItem((*dist)(gen)));
		// 	delete dist;
		// }
	}

	/// @brief Возвращает очередь объектов в виде вектора строк
	/// @return std::vector<std::string> result
	std::vector<std::string> ObjectsByStr()
	{
		std::vector<std::string> result;
		result.reserve(items->size());
		for (Objects &i: *items) result.push_back(translatorToString(i));
		return result;
	}

	std::vector<Objects> ReturnObjects() { return *items; }

	void clear() { items->clear(); }
	void erase(const Objects &object) 
	{ 
		for (unsigned i = 0; i < items->size(); ++i) // -1 or not
			if ((*items)[i] == object)
			{
				items->erase(items->cbegin() + i);
				break;
			}
	}

	/// @brief Деструктор
	~Items() { 
		std::cout << "Queue of items has been deleted (from Items)\n";
		delete items; 
	}
};