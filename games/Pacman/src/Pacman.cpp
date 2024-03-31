/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pacman.hpp"
#include <string>

extern "C" {
    std::unique_ptr<Pacman> create_game(void) {
        return nullptr;
    }

    const std::string &get_name(void) {
        const static std::string name = "Pacman";
        return name;
    }
}
