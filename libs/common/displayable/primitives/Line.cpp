/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/primitives/Line.hpp"
#include "common/utils/Coord2D.hpp"

Line::Line(std::unique_ptr<ICoordinate> &end, std::unique_ptr<IColor> &color, char replacingChar)
    : APrimitive(color, replacingChar)
{
    this->_end = std::move(end);
}

Line::Line(const ICoordinate &end, const IColor &color, char replacingChar)
    : APrimitive(color, replacingChar)
{
    this->_end = std::make_unique<Coord2D>(end.getX(), end.getY());
}

Line::Line(const ICoordinate &end, const RGBAColor &color, char replacingChar)
    : APrimitive(std::make_unique<RGBAColor>(color), replacingChar)
{
    this->_end = std::make_unique<Coord2D>(end.getX(), end.getY());
}

const ICoordinate &Line::getEnd() const
{
    return *this->_end;
}

void Line::setEnd(const ICoordinate &end)
{
    this->_end = std::make_unique<Coord2D>(end.getX(), end.getY());
}

void Line::setEnd(std::unique_ptr<ICoordinate> end)
{
    this->_end = std::move(end);
}
