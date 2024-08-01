#include "Mode.h"
#include "AI.h"
#include "Shotgun.h"

int main() { 
    //mains();
    AI_Player ai;
    ai.Dealer->getLives(6);
    ai.Dealer->generate_objects(8);
    ai.Dealer->damage(3);
    ai.Dealer->output_objects();
    ai.Dealer->getWeapon(new Shotgun);
    ai.analyze();
    std::cout << ai.Dealer->setLives() << std::endl;
    ai.Dealer->output_objects();

    system("pause");
}