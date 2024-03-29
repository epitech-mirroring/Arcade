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
    this->_picture = std::move(picture);
}

SimpleSprite::SimpleSprite(const std::string &path)
{
    this->_picture = std::make_unique<Picture>(path);
}

SimpleSprite::SimpleSprite(const SimpleSprite &sprite)
{
    this->_picture = std::make_unique<Picture>(sprite.getPicture().getPath());
}

const IPicture &SimpleSprite::getPicture() const
{
    return *this->_picture;
}

void SimpleSprite::setPicture(std::unique_ptr<IPicture> picture)
{
    this->_picture = std::move(picture);
}

void SimpleSprite::setPicture(const IPicture &picture)
{
    this->_picture = std::make_unique<Picture>(picture.getPath());
}
