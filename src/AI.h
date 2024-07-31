#pragma once

#include "OnePlayer.h"
#include "Shotgun.h"

class AI_Player
{
public:
    OnePlayer* Dealer = new OnePlayer("Dealer");
    //AI_Player(Shotgun *weapon) {  shotgun = weapon; }
    AI_Player() {}

    void analyze()
    {
        auto [full, empty] = Dealer->shotgun->setShot();
        if ((full + empty) < Dealer->setFullLives() && in_container(Dealer->ret_items(), CIGARETTE))
            while((full + empty) == Dealer->setFullLives() && Dealer->count_of_object(CIGARETTE) != 0)
                Dealer->use(CIGARETTE);
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