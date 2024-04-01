/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pacman.hpp"
#include <string>
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib()
    {
        std::cout << "Loading Pacman game" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib()
    {
        std::cout << "Unloading Pacman game" << std::endl;
    }

    std::unique_ptr<Pacman> create_game(void) {
        return nullptr;
    }

    const std::string &get_name(void) {
        const static std::string name = "Pacman";
        return name;
    }
}
