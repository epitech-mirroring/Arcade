/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/primitives/Circle.hpp"

Circle::Circle(std::unique_ptr<IColor> &color, std::size_t radius) : APrimitive(color) {
    _radius = radius;
}

size_t Circle::getRadius() const
{
    return _radius;
}

void Circle::setRadius(size_t radius)
{
    _radius = radius;
}
