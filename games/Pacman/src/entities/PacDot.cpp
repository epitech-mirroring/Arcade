/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "PacDot.hpp"

PacDot::PacDot(bool isEnergizer): AEntity("assets/games/pacman/walls.png", 143, 26)
{
    this->_isEnergizer = isEnergizer;
    this->_sprite->setDrawRect({117 + (this->_isEnergizer?18ul:0ul), 18, 8, 8});
    this->setSize(SCALE);
}

PacDot::PacDot(PacDot &pacDot):  AEntity("assets/games/pacman/walls.png", 143, 26)
{
    this->_isEnergizer = pacDot._isEnergizer;
}

bool PacDot::isEnergizer() const
{
    return _isEnergizer;
}

PacDot &PacDot::operator=(const PacDot &pacDot)
{
    this->_isEnergizer = pacDot._isEnergizer;
    return *this;
}
