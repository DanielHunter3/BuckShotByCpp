#include <iostream>

int main()
{
    int *ptr1 = new int(5);
    int *ptr2 = ptr1;

    std::cout << ptr1 << " : " << &ptr1 << " : " << *ptr1 << std::endl;
    std::cout << ptr2 << " : " << &ptr2 << " : " << *ptr2 << std::endl;

    ptr2 = nullptr; // Nullify the original pointer to prevent dangling reference
    std::cout << ptr1 << " : " << &ptr1 << " : " << *ptr1 << std::endl;
    std::cout << ptr2 << " : " << &ptr2 << " : " << *ptr2 << std::endl;
    delete ptr1;
}
