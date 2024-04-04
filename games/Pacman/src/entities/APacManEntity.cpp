/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "APacManEntity.hpp"

APacManEntity::APacManEntity(const std::string &texturePath, const std::size_t &width, const std::size_t &height)
    : AEntity(texturePath, width, height)
{
    _direction = Direction::UP;
}

Direction APacManEntity::getDirection() const
{
    return _direction;
}
