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
    this->_size = 1;
    this->_rotation = 0;
}

const ICoordinate &ADisplayable::getPosition() const
{
    return *this->_position;
}

int ADisplayable::getSize() const
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

void ADisplayable::setSize(int size)
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
