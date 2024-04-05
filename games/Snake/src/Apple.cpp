/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Apple
*/

#include "Apple.hpp"

Apple::Apple(int x, int y) : AEntity("./assets/games/Snake/apple.png", 40, 40)
{
    this->gridPos = Coord2D(x, y);
}

Apple::Apple(const Coord2D &pos) : AEntity("./assets/games/Snake/apple.png", 40, 40)
{
    this->gridPos = pos;
}

Coord2D Apple::getGridPos() const
{
    return this->gridPos;
}

