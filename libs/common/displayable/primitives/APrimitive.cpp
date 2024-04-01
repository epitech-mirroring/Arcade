/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/primitives/APrimitive.hpp"
#include "common/utils/RGBAColor.hpp"

APrimitive::APrimitive(std::unique_ptr<IColor> &color, char replacingChar)
{
    this->_color = std::move(color);
    this->_replacingChar = replacingChar;
}

APrimitive::APrimitive(const IColor &color, char replacingChar)
{
    this->_color = std::make_unique<RGBAColor>(color.getR(), color.getG(), color.getB(), color.getA());
    this->_replacingChar = replacingChar;
}

const IColor &APrimitive::getColor() const
{
    return *this->_color;
}

void APrimitive::setColor(const IColor &color)
{
    this->_color = std::make_unique<RGBAColor>(color);
}

void APrimitive::setColor(std::unique_ptr<IColor> color)
{
    this->_color = std::move(color);
}
