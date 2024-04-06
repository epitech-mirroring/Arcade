/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "LevelCounter.hpp"
#include "../PacmanGlobals.hpp"
#define LEVELS_SCALE (SCALE * 8. / 16.)

LevelCounter::LevelCounter()
    : AEntity("assets/games/pacman/level_counter.png", 112, 304)
{
    this->_level = 1;
    this->_sprite->setDrawRect({0, 0, 112, 16});
    this->setSize(LEVELS_SCALE);
    this->setPosition(GridCoordinate(MAP_WIDTH - 8, MAP_HEIGHT - 3).toScreen());
}

void LevelCounter::setLevel(std::size_t level)
{
    this->_level = level;
    this->_sprite->setDrawRect({0, 16 * (level - 1), 112, 16});
}
