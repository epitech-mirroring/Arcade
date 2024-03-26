/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Sdl2.hpp"
#include <memory>
#include <string>

extern "C" {
    std::unique_ptr<SDL2> create_driver(void)
    {
        return nullptr;
    }

    const std::string &get_name(void)
    {
        const static std::string name = "SDL2";
        return name;
    }
}