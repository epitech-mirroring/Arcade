/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/primitives/Circle.hpp"
#include "common/utils/RGBAColor.hpp"

Circle::Circle(std::unique_ptr<IColor> &color, std::size_t radius, char replacingChar): APrimitive(color, replacingChar) {
    this->_radius = radius;
}

Circle::Circle(const IColor &color, std::size_t radius, char replacingChar): APrimitive(color, replacingChar) {
    this->_radius = radius;
}

size_t Circle::getRadius() const
{
    return this->_radius;
}

void Circle::setRadius(size_t radius)
{
    this->_radius = radius;
}
