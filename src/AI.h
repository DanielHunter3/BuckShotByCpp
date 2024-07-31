#pragma once

#include "OnePlayer.h"
#include "Shotgun.h"

class AI_Player
{
private:
    Shotgun *shotgun;

public:
    OnePlayer* Dealer = new OnePlayer("Dealer");
    AI_Player(Shotgun *weapon) {  shotgun = weapon; }
    AI_Player() {}

    void analyze()
    {
        auto [full, empty] = shotgun->setShot();
    }
    void s() { 
        shotgun->del();
        shotgun->del();
        shotgun->del();
        shotgun->del();    
    }

    ~AI_Player() {
        std::cout << "AI_Player destructor called" << std::endl; 
        delete Dealer; 
    }
};