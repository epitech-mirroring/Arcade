/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/ADisplayable.hpp"
#include "common/utils/Coord2D.hpp"

ADisplayable::ADisplayable()
{
    this->_position = std::make_unique<Coord2D>(0, 0);
    this->_color = std::make_unique<RGBAColor>(255, 255, 255, 255);
    this->_size = 1;
    this->_rotation = 0;
    this->_replacingChar = ' ';
}

const ICoordinate &ADisplayable::getPosition() const
{
    return *this->_position;
}

float ADisplayable::getSize() const
{
    return this->_size;
}

void ADisplayable::setPosition(const ICoordinate &position)
{
    this->_position = std::make_unique<Coord2D>(position);
}

void ADisplayable::setPosition(std::unique_ptr<ICoordinate> position)
{
    this->_position = std::move(position);
}

void ADisplayable::setSize(float size)
{
    this->_size = size;
}

float ADisplayable::getRotation() const
{
    return this->_rotation;
}

void ADisplayable::setRotation(float angle)
{
    this->_rotation = angle;
}

char ADisplayable::getReplacingChar() const {
    return this->_replacingChar;
}

const IColor &ADisplayable::getColor() const
{
    return *this->_color;
}

void ADisplayable::setColor(const IColor &color)
{
    this->_color = std::make_unique<RGBAColor>(color);
}

void ADisplayable::setColor(std::unique_ptr<IColor> color)
{
    this->_color = std::move(color);
}
