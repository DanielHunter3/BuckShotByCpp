#pragma once

#include "OnePlayer.h"

class AI_Player
{
private:
    OnePlayer* Dealer = new OnePlayer("Dealer");

public:
    ~AI_Player() {
        std::cout << "AI_Player destructor called" << std::endl; 
        delete Dealer; 
    }

};