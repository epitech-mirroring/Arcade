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
    this->setColor(RGBAColor::WHITE);
}

void LiveCounter::setLives(std::size_t lives)
{
    this->_lives = lives;
    this->_sprite->setDrawRect({0, 16 * (5 - lives), 80, 16});
}

char LiveCounter::getReplacingChar() const
{
    if (this->_lives == 0)
        return '0';
    if (this->_lives == 1)
        return '1';
    if (this->_lives == 2)
        return '2';
    if (this->_lives == 3)
        return '3';
    if (this->_lives == 4)
        return '4';
    if (this->_lives == 5)
        return '5';
    return '0';
}
