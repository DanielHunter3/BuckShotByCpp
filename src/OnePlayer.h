#pragma once

#include <iostream>
#include <format>

#include "Item.h"
#include "Constant.h"
#include "Details.h"
#include "Shotgun.h"

class OnePlayer
{
public:
	Shotgun *shotgun;   //   ! Указатель на оружие

private:
	Items *items = new Items;  // ! Указатель
	std::string name; // * Имя игрока
	size_t hearts, copy_hearts;
	bool is_changeUp = false; // * Связан ли игрок наручниками

public:
	OnePlayer(std::string name, Shotgun *weapon) : name(name), shotgun(weapon) {}
	OnePlayer(std::string name) : name(name) {}
	OnePlayer() {}
	void getWeapon(Shotgun *weapon) { shotgun = weapon; }
	void rename(std::string name) { this->name = name; }
	std::string setName() { return name; }

	void getLives(size_t lives) { 
		hearts = lives; 
		copy_hearts = hearts;
	}
	size_t setLives() { return hearts; }
	size_t setFullLives() { return copy_hearts; }

	void damage(size_t damage) { hearts -= damage; }
	void death() { hearts = 0; }
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

	void generate_objects(size_t n) { items->generate(n); }
	void clear_objects() { items->clear(); }
	std::vector<Objects> ret_items() { return items->ReturnObjects(); };
	void output_objects() { items->show_objects(); }

	void use(Objects &&object) // & or &&
	{
		if (items->ReturnObjects().empty())
			std::cout << "No objects to use\n";
		else if (!in_container(items->ReturnObjects(), object))
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

	size_t count_of_object(Objects &&object) { return items->count_of_element(object); }
	
	/// @brief Деструктор
	~OnePlayer() { 
		delete items; 
		std::cout << "Objects has been deleted (from OnePlayer)\n";
	}
};
