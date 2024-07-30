#include "Mode.h"
#include "Item.h"
#include <iostream>

int main() { 
    //mains();
    int n;
    std::cin >> n;
    Items o;
    o.generate(n);
    o.show_objects();
    system("pause");
}