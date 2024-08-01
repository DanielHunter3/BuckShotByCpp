#include <iostream>
#include <thread>
#include <chrono>

void DoWork()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << i + 1 << " times\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main()
{
    std::thread t1(DoWork);

    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << " - " << i + 1 << " times\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    t1.join();
    return 0;
}