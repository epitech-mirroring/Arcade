/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/entities/SimpleSprite.hpp"
#include "common/utils/Picture.hpp"

SimpleSprite::SimpleSprite(std::unique_ptr<IPicture> picture)
{
    _picture = std::move(picture);
}

SimpleSprite::SimpleSprite(const std::string &path)
{
    _picture = std::make_unique<Picture>(path);
}

const std::unique_ptr<IPicture> &SimpleSprite::getPicture() const
{
    return _picture;
}

void SimpleSprite::setPicture(std::unique_ptr<IPicture> picture)
{
    _picture = std::move(picture);
}
