#pragma once

#include <iostream>
#include <stdlib.h>
#include <format>

#include "Shotgun.h"
#include "Player.h"
#include "Item.h"
#include "Details.h"
#include "Winda.h"
#include "Constant.h"
#include "Process.h"

void mains();

/// @brief Игра
void game()
{
    matrix();
    std::cout << color<Yellow, Black> << NAME_OF_GAME << color <LightGreen, Black>;

    std::string* name1 = new std::string;
    std::string* name2 = new std::string;

    check(*name1, 1);
    check(*name2, 2);

    TwoPlayers players(*name1, *name2);
    delete name1; delete name2;
    Shotgun shotgun;

    std::string answer_for_shot;

    for (int i = 1; i <= 3; ++i)
    {
        //if (i == 1)
        //{
        //    std::cout << "�����, ��� ������ ��������� �������...\nBring a shotgun and shot!\n";
        //    players.get(5);

        //    while (players.is_live() != 0) //***
        //    {
        //        shotgun.get(5, 5);       /
        //        shotgun.create_queue();  /
        //        shotgun.get_info();      /

        //        for (size_t k = 0; k < shotgun.size(); i++) //
        //            important_process(players, shotgun, answer_for_shot); //
        //    }
        //}

        switch (i)
        {
        case 1:
            std::cout << "Rules...\nBring a shotgun and shot!\n";
            players.get(5);
        }
    }
}

/// @brief Настройки игры
void settings()
{
    std::cout << std::format("Use command resize (enter) *name of element*\n\n1. Matrix: {}\n\n", length_matrix);
    std::cout << "Answer: ";

    std::string *answer = new std::string;
    bool *stg = new bool;

    *stg = true;
    std::cin >> *answer;

    if (*answer == "exit")
    {
        system("cls");
        //mains();
        *stg = false;
    }

    if (*answer == "help")
    {
        system("cls");
        std::cout << "/help\n\n/resize - ...\n/exit - ...\n";
        system("pause");
        system("cls");
        //settings();
    }

    if (*answer == "resize")
    {
        std::cout << "The name of settings: ";
        short element, n;
        std::cin >> element;

        switch (element)
        {
        case 1:
            std::cout << "Enter: ";
            std::cin >> n;
            re_length_matrix(n);
        }

        system("cls");
        //settings();
    }

    delete answer;
    *stg ? (delete stg, settings()) : (delete stg, mains());
}

/// @brief Главное меню
void mains()
{
    std::cout << color<Red, Black> << NAME << "\n\n\n";
    std::string *mainstr = new std::string;

    std::cout << color<Yellow, Black> << MENU << color << "\n\n\n" << ENTER;
    std::cin >> *mainstr;

    system("cls");
    if (*mainstr == "new") 
    {
        delete mainstr;
        game();
    }
    else if (*mainstr == "settings") 
    {
        delete mainstr;
        settings();
    }
    else if (*mainstr == "exit") 
    {
        delete mainstr;
        exit(0);
    }
    else 
    {
        delete mainstr;
        goto stop;
        stop: std::cout << "Error 404";
    }
}
