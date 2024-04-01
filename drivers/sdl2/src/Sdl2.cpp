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
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib()
    {
        std::cout << "Loading SDL2 driver" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib()
    {
        std::cout << "Unloading SDL2 driver" << std::endl;
    }

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
