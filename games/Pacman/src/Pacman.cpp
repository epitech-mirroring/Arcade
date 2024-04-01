/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pacman.hpp"
#include "common/utils/Coord2D.hpp"
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
        return std::make_unique<Pacman>();
    }

    const std::string &get_name(void) {
        const static std::string name = "Pacman";
        return name;
    }
}

Pacman::Pacman() {
}

void Pacman::start() {
    std::size_t scale = 2;
    for (std::size_t y = 0; y < MAP_HEIGHT; y++) {
        for (std::size_t x = 0; x < MAP_WIDTH; x++) {
            Coord2D pos = Coord2D((int) (x*8*scale), (int) (y*8*scale));
            this->_map[y][x].setPosition(pos);
            this->_map[y][x].setSize((float) scale);
        }
    }
    this->_arcade->setPreferredSize(MAP_WIDTH*8*scale, MAP_HEIGHT*8*scale);
}

void Pacman::run() {
    // Draw map
    for (auto & line : this->_map) {
        for (const auto & piece : line) {
            this->_arcade->display(piece);
        }
    }

    this->_arcade->flipFrame();
}