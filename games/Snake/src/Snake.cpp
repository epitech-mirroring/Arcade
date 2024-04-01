/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Snake.hpp"
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib() {
        std::cout << "Loading Snake game" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib() {
        std::cout << "Unloading Snake game" << std::endl;
    }

    std::unique_ptr<IGame> create_game() {
        return nullptr;
    }

    const std::string &get_name() {
        static const std::string game_name = "Snake";
        return game_name;
    }
}
