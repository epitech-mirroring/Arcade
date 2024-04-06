/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "LiveCounter.hpp"
#include "../PacmanGlobals.hpp"
#include "../utils/GridCoordinate.hpp"
#define LIVES_SCALE (SCALE * 8. / 16.)

LiveCounter::LiveCounter()
        : AEntity("assets/games/pacman/pacman/lives_counter.png", 80, 80)
{
    this->_lives = 4;
    this->_sprite->setDrawRect({0, 16, 80, 16});
    this->setSize(LIVES_SCALE);
    this->setPosition(GridCoordinate(4, MAP_HEIGHT - 3).toScreen());
}

void LiveCounter::setLives(std::size_t lives)
{
    this->_lives = lives;
    this->_sprite->setDrawRect({0, 16 * (5 - lives), 80, 16});
}
