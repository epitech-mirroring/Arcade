/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "AGhost.hpp"

AGhost::AGhost(const std::string &texturePath): APacManEntity(texturePath, 16, 16)
{
    _isDead = false;
}

bool AGhost::isDead() const
{
    return _isDead;
}

bool AGhost::hasToReverse() const
{
    return _hasToReverse;
}
