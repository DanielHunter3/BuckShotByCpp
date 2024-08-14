#include "windows.h"
#include <iostream>
#include <string>
#include <thread>

void output_text(std::string text)
{
    for (auto &i: text)
    {
        std::cout << i;
        Sleep(100); //100
    }
}

int main()
{
    std::string text = R"(
"Hello, World!"
fffssd
    )";
    output_text(text);
}