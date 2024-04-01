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
    this->_drawRect = {0, 0, this->_picture->getWidth(), this->_picture->getHeight()};
}

SimpleSprite::SimpleSprite(const std::string &path, const std::size_t &width, const std::size_t &height)
{
    this->_picture = std::make_unique<Picture>(path, width, height);
    this->_drawRect = {0, 0, this->_picture->getWidth(), this->_picture->getHeight()};
}

SimpleSprite::SimpleSprite(const ISprite &sprite)
{
    this->_picture = std::make_unique<Picture>(sprite.getPicture());
    this->_drawRect = sprite.getDrawRect();
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
    this->_picture = std::make_unique<Picture>(picture);
}

const DrawRect &SimpleSprite::getDrawRect() const
{
    return this->_drawRect;
}

void SimpleSprite::setDrawRect(const DrawRect &drawRect)
{
    this->_drawRect = drawRect;
}
