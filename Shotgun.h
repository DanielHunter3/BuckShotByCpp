#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class Shotgun 
{
private:
    std::vector<bool> *queue = new std::vector<bool>();
    size_t full, empty;
    short shotgun_damage = 1;

public:
    void get(size_t full, size_t empty) {
        this->full = full;
        this->empty = empty;
    }

    void create_queue() 
    {
        queue->reserve(full + empty);
        std::vector<bool> vec(full, true);
        vec.insert(vec.end(), empty, false);

        std::random_device rnd;
        std::mt19937 gen(rnd());
        std::shuffle(vec.begin(), vec.end(), gen);

        *queue = vec;
    }

    void print_queue() {
        std::cout << "[ ";
        for (const auto& shot : *queue) {
            std::cout << shot << ' ';
        }
        std::cout << ']' << std::endl << queue->size() << '\n';
    }

    bool fire() { return queue->back(); }
    void del() { queue->pop_back(); }
    void clear() { full = empty = 0; queue->clear(); }

    void get_info() { printf("Full: %zd\nEmpty: %zd", full, empty); }
    size_t size() { return queue->size(); }

    short return_damage() { return shotgun_damage; }
    void swap_damage() { shotgun_damage = (shotgun_damage == 1) ? 2 : 1; }

    ~Shotgun() { 
        clear();  // Clean up the vector and delete the pointer
        delete queue;
        std::cout << "Queue of shots has been deleted (from Shotgun)\n";
    }
};