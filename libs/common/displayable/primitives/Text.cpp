/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#include "common/displayable/primitives/Text.hpp"

Text::Text(std::unique_ptr<IColor> &color, const std::string &text)
    : APrimitive(color)
{
    _text = text;
}

const std::string &Text::getText() const
{
    return _text;
}

void Text::setText(const std::string &text)
{
    _text = text;
}
