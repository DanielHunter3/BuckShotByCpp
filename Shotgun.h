#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <stdio.h>

// TODO: #include "Player.h"

class Shotgun 
{
private:
	// ! Это указатель! Очищается в деструкторе.
	std::vector<bool> *queue = new std::vector<bool>; // * Очередь патронов (full - true, empty - false)
	size_t full, empty;       // * full - полный, empty - пустой
	short shotgun_damage = 1; // * Урон

public:

	/// @brief Ввести кол-во полных и пустых патронов
	/// @param full полный патрон
	/// @param empty пустой патрон
	void get(size_t full, size_t empty) {
		this->full = full;
		this->empty = empty;
	}

	/// @brief Создание очереди патронов
	void create_queue() 
	{
		std::vector<bool> vec;
		std::random_device rnd;
		std::mt19937 gen(rnd());
		
		for (unsigned i = 0; i < full; ++i) vec.push_back(true);
		for (unsigned i = 0; i < empty; ++i) vec.push_back(false);
		
		while (vec.size() != 0)
		{
			std::uniform_int_distribution<size_t> *dist = new std::uniform_int_distribution<size_t>(0, vec.size() - 1); // ! Указатель
			size_t *randindex = new size_t; // ! Указатель

			*randindex = (*dist)(gen);
			queue->push_back(vec[*randindex]);
			vec.erase(vec.begin() + *randindex);

			delete randindex;   // ! Очистить указатель
			delete dist;        // ! Очистить указатель
		}
	}

	/// @brief Вывести очередь патронов
	void print_queue() {
		std::cout << "[ ";
		for (int i = 0; i < queue->size(); ++i) std::cout << (*queue)[i] << ' ';
		std::cout << ']' << std::endl << queue->size();
	}

	/// @brief Возвращает первый патрон в обойме
	/// @return bool первый патрон в типе true || false
	bool fire() { return queue->back(); }
	/// @brief Удалить первый патрон в обойме
	void del() { queue->pop_back(); }
	/// @brief Очистить все данные
	void clear() 
	{ 
		full = empty = 0;
		queue->clear(); 
	}

	/// @brief Пишет кол-во полных и пустых патронов
	void get_info() { printf("Full: %zd\nEmpty: %zd", full, empty); }
	/// @brief Возвращает кол-во патронов в очереди
	/// @return size_t queue->size()
	size_t size() { return queue->size(); }

	/// @brief Возвращает урон
	/// @return short shotgun_damage
	short return_damage() { return shotgun_damage; }
	/// @brief Сменить кол-во урона
	void swap_damage() { shotgun_damage = (shotgun_damage == 1) ? 2 : 1; } //shotgun_damage == 1 ? shotgun_damage = 2 : shotgun_damage = 1;

	/// @brief Деструктор
	~Shotgun() { 
		std::cout << "Shotgun has been deleted\n";
		clear();
		delete queue; 
	}
};