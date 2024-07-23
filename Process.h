#pragma once

#include <iostream>

#include "Shotgun.h"
#include "Player.h"
#include "Details.h"

/// @brief Где всё происходит
/// @param players игроки
/// @param shotgun дробовик
/// @param isItems наличие предметов
void important_process(TwoPlayers &players, Shotgun &shotgun) // TODO: bool isItems
{
    while (true)
    {std::cout << players.show_area() << std::endl;
        std::string *answer = new std::string;

        std::cout << color<LightRed, Black> << "Your foe" << color<LightCyan, Black>
            << " or " << color<LightGreen, Black> << "you" << color<Magenta, Black> << "?" << color;

        while (true)
        {
            std::cin >> *answer;
            if (in_array(iii, *answer) || in_array(another, *answer)) break;
            else std::cout << "Try again: ";
        }

        if (in_array(iii, *answer))
        {
            players.reverse_turn_for_damage(false);
        
            if (shotgun.fire()) 
            {
                players.damage(shotgun.return_damage());
                std::cout << color<LightRed, Black> << "Oh, no! You are hurted!" << color;
                players.reverse_turn();
            }
            else std::cout << color<LightGreen, Black> << "Yes, you are lucky!" << color;
        }

        else
        {
            players.reverse_turn_for_damage(true);

            if (shotgun.fire()) 
            {
                players.damage(shotgun.return_damage()); // seeMyArea();
                std::cout << color<LightGreen, Black> << "Yes, you could hurt your foe!" << color;
            }
            else 
            {
                std::cout << color<LightRed, Black> << "Oh, no! You could not hurt your foe!" << color;
                players.return_turn();
            }  
        }

        delete answer;
    }
}

void important_process_objects(TwoPlayers &players, Shotgun &shotgun, short quantity)
{
    std::cout << players.show_area() << std::endl;
    std::string *answer = new std::string;

    std::cout << "Use objects? (Y/n): ";
    std::cin >> *answer;

    if (*answer == "Y")
    {
        players.show_objects();
        // TODO: Повторный запрос
    }

    std::cout << color<LightRed, Black> << "Your foe" << color<LightCyan, Black>
        << " or " << color<LightGreen, Black> << "you" << color<Magenta, Black> << "?" << color;

    while (true)
    {
        std::cin >> *answer;
        if (in_array(iii, *answer) || in_array(another, *answer)) break;
        else std::cout << "Try again: ";
    }

    if (in_array(iii, *answer))
    {
        players.reverse_turn_for_damage(false);
        
        if (shotgun.fire()) 
        {
            players.damage(shotgun.return_damage());
            std::cout << color<LightRed, Black> << "Oh, no! You are hurted!" << color;
            players.reverse_turn();
        }
        else std::cout << color<LightGreen, Black> << "Yes, you are lucky!" << color;
    }

    else
    {
        players.reverse_turn_for_damage(true);

        if (shotgun.fire()) 
        {
            players.damage(shotgun.return_damage()); // seeMyArea();
            std::cout << color<LightGreen, Black> << "Yes, you could hurt your foe!" << color;
        }
        else 
        {
            std::cout << color<LightRed, Black> << "Oh, no! You could not hurt your foe!" << color;
            players.return_turn();
        }
    }

    delete answer;
}