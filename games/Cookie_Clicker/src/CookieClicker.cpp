/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "CookieClicker.hpp"
#include "common/displayable/entities/SimpleEntity.hpp"
#include "common/utils/Coord2D.hpp"
#include <iostream>

#define HEIGHT 900
#define WIDTH 1440

extern "C" {
    __attribute__((constructor))
    void load_lib() {
        std::cout << "Loading Snake" << std::endl;
    }

    __attribute__((destructor))
    void unload_lib() {
        std::cout << "Unloading Snake" << std::endl;
    }

    std::unique_ptr<IGame> create_game() {
        std::unique_ptr<IGame> game = std::make_unique<CookieClicker>();
        return game;
    }

    const std::string &get_name() {
        static const std::string game_name = "Cookie Clk.";
        return game_name;
    }
}

CookieClicker::CookieClicker() = default;

void CookieClicker::start() {
    this->_arcade->setPreferredSize(WIDTH, HEIGHT);
}

void CookieClicker::run() {
    // Flip the frame
    this->_arcade->flipFrame();
}
