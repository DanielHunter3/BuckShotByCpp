#include <iostream>

int main()
{
    int *p1 = new int;
    int *p2 = p1;
    p2 = p1;
    delete p1;
    p2 = nullptr;
    std::cout << "H";
    return 0;
}