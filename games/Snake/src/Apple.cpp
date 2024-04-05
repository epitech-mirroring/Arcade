/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Apple
*/

#include "Apple.hpp"

Apple::Apple(int x, int y) : AEntity("./assets/games/Snake/apple.png", 40, 40)
{
    this->pos = Coord2D(x, y);
}

Apple::Apple(const Coord2D &pos) : AEntity("./assets/games/Snake/apple.png", 40, 40)
{
    this->pos = pos;
}

Apple::~Apple()
{
}

Coord2D Apple::getPos() const
{
    return this->pos;
}

