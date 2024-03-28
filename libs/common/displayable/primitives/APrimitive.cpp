/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/primitives/APrimitive.hpp"

APrimitive::APrimitive(std::unique_ptr<IColor> &color)
{
    _color = std::move(color);
}

const std::unique_ptr<IColor> &APrimitive::getColor() const
{
    return _color;
}
