/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/primitives/Square.hpp"

Square::Square(std::unique_ptr<IColor> &color, size_t width, size_t height) : APrimitive(color)
{
    this->_width = width;
    this->_height = height;
}

Square::Square(const IColor &color, size_t width, size_t height) : APrimitive(color)
{
    this->_width = width;
    this->_height = height;
}

size_t Square::getWidth() const
{
    return this->_width;
}

size_t Square::getHeight() const
{
    return this->_height;
}

void Square::setWidth(size_t width)
{
    this->_width = width;
}

void Square::setHeight(size_t height)
{
    this->_height = height;
}
