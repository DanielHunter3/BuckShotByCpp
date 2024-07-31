#pragma once

#include "OnePlayer.h"
#include "AI.h"
#include "Item.h"
#include "Shotgun.h"
#include "AI.h"

class TwoPlayers
{
private:
	enum Turn { Player, AI }; //First, Second
	enum Turn_for_damage { OnPlayer, OnAI }; //first_damage, second_damage
	Shotgun *shotgun = new Shotgun; // * new shotgun
	OnePlayer player; // * player
	AI_Player dealer; // * dealer (AI)
	Turn turn = Turn::Player; // * Очередь стрелять или использовать предеметы игрока
	Turn_for_damage turn_for_damage; // * В кого стрелять

public:
	/// @brief Конструктор
	/// @param name1 имя первого игрока
	/// @param name2 имя второго игрока
	TwoPlayers(std::string name)  
	{
		player.rename(name);
		dealer = AI_Player(shotgun);
	}

	/// @brief Задаёт кол-во жизней для каждого из игроков
	/// @param lives кол-во жизней для каждого из игроков
	void get(size_t lives) 
	{
		player.getLives(lives);
		dealer.Dealer->getLives(lives);
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
	{ return std::min(player.setLives(), dealer.Dealer->setLives()); }

	/// @brief Регенирируем того или иного игрока
	void regeneration() // ? Может убрать параметр Turn &human и регенить по автомату?
	{ 
		// human == First ? player1.regeneration() : player2.regeneration();
		(turn == Player) ? player.regeneration() : dealer.Dealer->regeneration();
	}

	/// @brief Наносит урон тому или иному игроку
	/// @param damage кол-во урона
	void damage(size_t damage)
	{ turn_for_damage == OnPlayer ? player.damage(damage) : dealer.Dealer->damage(damage); }
	/// @brief Reverse turn
	void reverse_turn()
	{
		//turn == First ? turn = Second : turn = First; 
		turn = (turn == Player) ? AI : Player;
	}

	// void generate_objects(size_t n) 
	// {
	// 	(turn == Player) ? player.generate_objects(n) : dealer.Dealer->generate_objects(n);
	// }
	// void show_objects(Turn parameter)
	// {
	// 	(parameter == Player) ? player.output_objects() : dealer.Dealer->output_objects();
	// }

	/// @brief Показать графически все данные
	/// @return std::string
	void show_area()
	{
		dealer.Dealer->output_objects();
		std::cout <<  std::format(
			"{}: {}\n{}\n{}: {}\n", 
			dealer.Dealer->setName(), dealer.Dealer->setLives(),
			AREA,
			player.setName(), player.setLives()
		);
		player.output_objects();
	}

	void generate(size_t n)
	{
		player.generate_objects(n);
		dealer.Dealer->generate_objects(n);
	}

	/// @brief Reverse turn for damage
	/// @param enemy если true, то на врага, иначе - на себя
	void reverse_turn_for_damage(bool enemy) //(Turn_for_damage tfd)
	{
		std::map<Turn, Turn_for_damage> map_for_damage;

		if (enemy)
		{
			map_for_damage[Player] = OnAI;
			map_for_damage[AI] = OnPlayer;
		}
		else
		{
			map_for_damage[Player] = OnPlayer;
			map_for_damage[AI] = OnAI;
		}
		turn_for_damage = map_for_damage[turn];
	}

	std::vector<Objects> user_objects()
	{
		return ( turn == Player ? player.ret_items() : dealer.Dealer->ret_items() );
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
