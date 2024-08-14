#pragma once

#include "OnePlayer.hpp"
#include "Details.hpp"

class AI_Player
{
private: 
    // ? num Action { OnPlayer, Undefined, OnAI };  // ?
                                    //  { a, b }
    // ? std::pair<short, short> _procention {50, 50}; // ? a - Player, b - AI
    bool _moving;   // ? cash variable for movement

public:
    bool shot_on_player;  // ?
    OnePlayer* Dealer = new OnePlayer("Dealer");  // ! Удаляется в деструкторе
    //AI_Player(Shotgun *weapon) {  shotgun = weapon; }
    AI_Player() {}

    void heal()
    {
        // Logic for healing player
        if (Dealer->setLives() < Dealer->setFullLives() && in_container(Dealer->ret_items(), CIGARETTE))
        {
            while(Dealer->setLives() != Dealer->setFullLives() && Dealer->count_of_object(CIGARETTE) != 0) //logic
            {
                output_text("(Dealer is using cigarette)\n");
                Dealer->use(CIGARETTE);
            }
        }
    }

    void equal_shots()
    {
        // Logic for equal shots
        if (in_container(Dealer->player->ret_items(), MAGNIFIER))
        {
            output_text("(Dealer is using magnifier)\nDealer: \"Very Interesting\"\n");
            _moving = (Dealer->shotgun->fire()) ? true : false;
            Dealer->use(MAGNIFIER);
        }

        else if (in_container(Dealer->player->ret_items(), BEER))
        {
            output_text("(Dealer is using beer)\n");
            Dealer->use(BEER);
            // 
        }

        else _moving = randint(); // Рандом, преобразует int в bool
    }

    void analyze()
    {
        auto [full, empty] = Dealer->shotgun->setShot();
        heal();
        if (full == empty)
        {
            if (in_container(Dealer->player->ret_items(), MAGNIFIER))
            {
                output_text("(Dealer is using magnifier)\nDealer: \"Very Interesting\"\n");
                shot_on_player = (Dealer->shotgun->fire()) ? true : false;
                Dealer->use(MAGNIFIER);
            }
            else shot_on_player = randint();
        }
        if (full - empty >= 2)
        {

        }

        if (shot_on_player && in_container(Dealer->ret_items(), KNIFE))
        {
            output_text("(Dealer is using knife)\n");
            Dealer->use(KNIFE);
            shot_on_player = false;
        }
    }
    void test() {  // tests for AI_Player class
        // do something here
    }

    ~AI_Player() {
        std::cout << "AI_Player destructor called" << std::endl; 
        delete Dealer; // ! Delete after the object has been destroyed
    }
};