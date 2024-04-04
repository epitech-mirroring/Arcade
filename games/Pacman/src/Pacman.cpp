/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pacman.hpp"
#include "common/utils/Coord2D.hpp"
#include "common/utils/RGBAColor.hpp"
#include "common/displayable/primitives/Text.hpp"
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

Pacman::Pacman() = default;
bool isFrightened = false;
int currentLevel = 0;
std::shared_ptr<IArcade> arcade;

void Pacman::start() {
    arcade = this->_arcade;
    for (std::size_t y = 0; y < MAP_HEIGHT; y++) {
        for (std::size_t x = 0; x < MAP_WIDTH; x++) {
            this->_map[y][x].setPosition(Coord2D(COORD_TO_SCREEN(x), COORD_TO_SCREEN(y)));
        }
    }
    this->_arcade->setPreferredSize(COORD_TO_SCREEN(MAP_WIDTH), COORD_TO_SCREEN(MAP_HEIGHT));

    // Bind keys
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_Z, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_Q, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_S, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_D, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_UP, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_DOWN, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_RIGHT, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });
    this->_arcade->bindEvent(IEvent::EventType::_KEY_PRESS, _KEY_LEFT, [this](const IEvent &event) {
        this->pac.handleEvent(event);
    });

    currentLevel = 0;
    isFrightened = false;
    this->_score = 0;
    this->replaceDots();
}

void Pacman::replaceDots() {
    for (auto & dot : this->dots) {
        delete &dot;
    }
    this->dots.clear();

    for (auto & line : this->_map) {
        for (auto & cell : line) {
            if (cell.getType() == Wall::WallType::DOT || cell.getType() == Wall::WallType::ENERGIZER) {
                auto *dot = new PacDot(cell.getType() == Wall::WallType::ENERGIZER);
                dot->setPosition(cell.getPosition());
                this->dots.push_back(dot);
            }
        }
    }
}

void Pacman::run() {
    // Draw map
    for (auto & line : this->_map) {
        for (const auto & piece : line) {
            this->_arcade->display(piece);
        }
    }
    // Draw dots
    for (auto & dot : this->dots) {
        this->_arcade->display(*dot);
    }
    // Update ghosts
    // Update pacman
    this->pac.update(this->dots, this->_map);
    // Display pacman
    this->_arcade->display(this->pac);
    // Display ghosts

    this->_arcade->flipFrame();
}