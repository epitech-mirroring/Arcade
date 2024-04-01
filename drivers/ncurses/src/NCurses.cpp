/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "NCurses.hpp"
#include <memory>
#include <string>
#include <iostream>

extern "C" {
    __attribute__((constructor))
    void load_lib()
    {
        std::cout << "Loading NCurses driver" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib()
    {
        std::cout << "Unloading NCurses driver" << std::endl;
    }

    std::unique_ptr<NCurses> create_driver(void)
    {
        return nullptr;
    }

    const std::string &get_name(void)
    {
        const static std::string name = "NCurses";
        return name;
    }
}
