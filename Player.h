#pragma once

#include <iostream>
#include <format>
#include <map>
#include <memory>

#include "Item.h"
#include "Constant.h"
#include "Details.h"
#include "Shotgun.h"

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
	/// @brief Задаёт игроку имя
	/// @param name имя игрока
	void rename(std::string name) { this->name = name; }
	/// @brief Возвращает имя игрока
	/// @return std::string name
	std::string return_name() { return name; }

	/// @brief Задаёт игроку кол-во ХП
	/// @param lives кол-во начальных жизней игрока
	void get(size_t lives) { hearts = copy_hearts = lives; }
	/// @brief Возвращает кол-во ХП игрока
	/// @return size_t hearts
	size_t set() { return hearts; }

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

class TwoPlayers
{
public:
	enum Turn { First, Second };
	enum Turn_for_damage { first_damage, second_damage };
	Shotgun *shotgun = new Shotgun;

private:
	OnePlayer player1, player2; // * 2 игрока
	Turn turn = First; // * Очередь стрелять или использовать предеметы игрока
	Turn_for_damage turn_for_damage; // * В кого стрелять

public:
	/// @brief Конструктор
	/// @param name1 имя первого игрока
	/// @param name2 имя второго игрока
	TwoPlayers(std::string name1, std::string name2)  
	{
		player1.rename(name1);
		player2.rename(name2);
	}

	/// @brief Задаёт кол-во жизней для каждого из игроков
	/// @param lives кол-во жизней для каждого из игроков
	void get(size_t lives) 
	{
		player1.get(lives);
		player2.get(lives);
	}

	//void get_shotgun(Shotgun *weapon) { shotgun = weapon; }

	/// @brief Возвращает очередь
	/// @return Player::TwoPlayers::Turn turn
	Turn return_turn() { return turn; }
	/// @brief В кого стреляёт, того и возвращает
	/// @return Player::TwoPlayers::Turn_for_damage turn_for_damage
	Turn_for_damage return_turn_for_damage() { return turn_for_damage; };

	/// @brief Выводит мин-ХП игрока
	/// @return size_t std::min(player1.set(), player2.set())
	size_t is_live()
	{ return std::min(player1.set(), player2.set()); }

	/// @brief Регенирируем того или иного игрока
	void regeneration() // ? Может убрать параметр Turn &human и регенить по автомату?
	{ 
		// human == First ? player1.regeneration() : player2.regeneration();
		(turn == First) ? player1.regeneration() : player2.regeneration();
	}

	/// @brief Наносит урон тому или иному игроку
	/// @param damage кол-во урона
	void damage(size_t damage)
	{ turn_for_damage == first_damage ? player1.damage(damage) : player2.damage(damage); }
	/// @brief Reverse turn
	void reverse_turn()
	{
		//turn == First ? turn = Second : turn = First; 
		turn = (turn == First) ? Second : First;
	}

	void generate_objects(size_t n) 
	{
		(turn == First) ? player1.generate_objects(n) : player2.generate_objects(n);
	}
	void show_objects()
	{
		(turn == First) ? player1.println_objects() : player2.println_objects();
	}

	/// @brief Показать графически все данные
	/// @return std::string
	std::string show_area()
	{
		std::string user1 = std::format("{}: {}", player1.return_name(), player1.set());
		std::string user2 = std::format("{}: {}", player2.return_name(), player2.set());
		return ((turn == First) ?
			std::format("{}\n{}\n{}", user2, AREA1, user1) :
			std::format("{}\n{}\n{}", user1, AREA2, user2));
	}

	/// @brief Reverse turn for damage
	/// @param enemy если true, то на врага, иначе - на себя
	void reverse_turn_for_damage(bool enemy) //(Turn_for_damage tfd)
	{
		std::map<Turn, Turn_for_damage> map_for_damage;

		if (enemy)
		{
			map_for_damage[First] = second_damage;
			map_for_damage[Second] = first_damage;
		}
		else
		{
			map_for_damage[First] = first_damage;
			map_for_damage[Second] = second_damage;
		}
		turn_for_damage = map_for_damage[turn];
	}

	std::vector<Objects> user_objects()
	{
		return ( turn == First ? player1.ret_items() : player2.ret_items() );
	}

	void use(Objects &object)
	{
		if (user_objects().empty())
			std::cout << "No objects to use\n";
		else if (!in_container(user_objects(), object))
			std::cout << "The object was not found\n";
		else
		{
			switch (object)
			{
				case CIGARETTE:
                    regeneration();
					std::cout << "The cigarette has been used\n";
                    break;
				case BEER:
				    std::cout << "The beer has been used\n";
					std::cout << (shotgun->fire() ? "FULL" : "EMPTY") << std::endl;
					shotgun->del();
                    break;
                case MAGNIFIER:
				    std::cout << "The magnifier has been used\n";
					std::cout << (shotgun->fire() ? "FULL" : "EMPTY") << std::endl;
                    break;
				case KNIFE:
				    std::cout << "The knife has been used\n";
                    shotgun->swap_damage();
                    break;
                default:
                    std::cout << "Unknown object\n";
                    break;
			}
		}
	}

	~TwoPlayers()
	{ 
		delete shotgun;
		std::cout << "Shotgun has been deleted (from TwoPlayers)\n"; 
	}
};
