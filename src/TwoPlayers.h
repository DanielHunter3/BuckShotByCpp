#pragma once

#include "OnePlayer.h"
#include "AI.h"
#include "Item.h"
#include "Shotgun.h"

class TwoPlayers
{
private:
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
		player1.getLives(lives);
		player2.getLives(lives);
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
	{ return std::min(player1.setLives(), player2.setLives()); }

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
		std::string user1 = std::format("{}: {}", player1.setName(), player1.setLives());
		std::string user2 = std::format("{}: {}", player2.setName(), player2.setLives());
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
