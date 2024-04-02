/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/primitives/Square.hpp"

Square::Square(std::unique_ptr<IColor> &color, size_t width, size_t height, bool isFilled, char replacingChar) : APrimitive(color, replacingChar)
{
    this->_width = width;
    this->_height = height;
    this->_isFilled = isFilled;
}

Square::Square(const IColor &color, size_t width, size_t height, bool isFilled, char replacingChar) : APrimitive(color, replacingChar)
{
    this->_width = width;
    this->_height = height;
    this->_isFilled = isFilled;
}

Square::Square(const ISquare &square) : APrimitive(square.getColor(), square.getReplacingChar())
{
    this->_width = square.getWidth();
    this->_height = square.getHeight();
    this->_isFilled = square.isFilled();
}

Square::Square(const Square &square) : APrimitive(square.getColor(), square.getReplacingChar())
{
    this->_width = square.getWidth();
    this->_height = square.getHeight();
    this->_isFilled = square.isFilled();
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

bool Square::isFilled() const
{
    return this->_isFilled;
}

void Square::setIsFilled(bool isFilled)
{
    this->_isFilled = isFilled;
}
