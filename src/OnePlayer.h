#pragma once

#include <iostream>

#include "Item.h"
#include "Constant.h"
#include "Details.h"

class OnePlayer
{
private:
	// ! Указатель
	Items *items = new Items;
	std::string name; // * Имя игрока
	size_t hearts;    // * Кол-во ХП игрока
	size_t copy_hearts;  // * Копия hearts
	bool is_changeUp = false; // * Связан ли игрок наручниками

public:
	OnePlayer(std::string name) : name(name) {}
	OnePlayer() {}
	/// @brief Задаёт игроку имя
	/// @param name имя игрока
	void rename(std::string name) { this->name = name; }
	/// @brief Возвращает имя игрока
	/// @return std::string name
	std::string setName() { return name; }

	/// @brief Задаёт игроку кол-во ХП
	/// @param lives кол-во начальных жизней игрока
	void getLives(size_t lives) { hearts = copy_hearts = lives; }
	/// @brief Возвращает кол-во ХП игрока
	/// @return size_t hearts
	size_t setLives() { return hearts; }
	size_t setFullLives() { return copy_hearts; }

	/// @brief Наносит игроку урон
	/// @param damage кол-во урона
	void damage(size_t damage) { hearts -= damage; }
	/// @brief Игрок умер
	void death() { hearts = 0; }
	/// @brief Восстанавливает игроку по одному ХП
	void regeneration()
	{
		if (!in_container(items->ReturnObjects(), CIGARETTE)) std::cout << "Object is undefined";
		else
		{
			if (hearts >= copy_hearts) std::cout << "Do not real!";
			else 
			{
				++hearts;
				items->erase(CIGARETTE);
			}
		}
	}

	/// @brief Генерирует список объектов
	/// @param n кол-во объектов
	void generate_objects(size_t n) { items->generate(n); }
	/// @brief Очищает список объектов
	void clear_objects() { items->clear(); }
	/// @brief Выводит объекты
	void println_objects()
	{ for (std::string &i: items->ObjectsByStr()) std::cout << i << '\n'; }
	std::vector<Objects> ret_items() { return items->ReturnObjects(); };
	
	/// @brief Деструктор
	~OnePlayer() { 
		delete items; 
		std::cout << "Objects has been deleted (from OnePlayer)\n";
	}
};
