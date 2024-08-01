#pragma once

#include "OnePlayer.h"
#include "Details.h"

class AI_Player
{
public:
    OnePlayer* Dealer = new OnePlayer("Dealer");
    //AI_Player(Shotgun *weapon) {  shotgun = weapon; }
    AI_Player() {}

    void analyze()
    {
        auto [full, empty] = Dealer->shotgun->setShot();
        if (Dealer->setLives() < Dealer->setFullLives() && in_container(Dealer->ret_items(), CIGARETTE))
        {
            while(Dealer->setLives() != Dealer->setFullLives() && Dealer->count_of_object(CIGARETTE) != 0) //logic
            {
                output_text("(Dealer is using cigarette)\n");
                Dealer->use(CIGARETTE);
            }
        }
    }
    void s() {
        Dealer->shotgun->del();
        Dealer->shotgun->del();
        Dealer->shotgun->del();
        Dealer->shotgun->del();   
    }

    ~AI_Player() {
        std::cout << "AI_Player destructor called" << std::endl; 
        delete Dealer; 
    }
};