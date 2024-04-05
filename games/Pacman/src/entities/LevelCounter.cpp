/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "LevelCounter.hpp"

LevelCounter::LevelCounter()
    : AEntity("assets/games/pacman/level_counter.png", 112, 304)
{
    this->_level = 1;
    this->_sprite->setDrawRect({0, 0, 112, 16});
}

void LevelCounter::setLevel(std::size_t level)
{
    this->_level = level;
    this->_sprite->setDrawRect({0, 16 * (level - 1), 112, 16});
}
