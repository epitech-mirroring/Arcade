/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/entities/AEntity.hpp"
#include "common/displayable/entities/SimpleSprite.hpp"

AEntity::AEntity(std::unique_ptr<ISprite> sprite, char replacingChar)
{
    this->_sprite = std::move(sprite);
    this->_replacingChar = replacingChar;
    this->_color = std::make_unique<RGBAColor>(255, 255, 255, 255);
}

AEntity::AEntity(const ISprite &sprite, char replacingChar)
{
    this->_sprite = std::make_unique<SimpleSprite>(sprite);
    this->_replacingChar = replacingChar;
    this->_color = std::make_unique<RGBAColor>(255, 255, 255, 255);
}

AEntity::AEntity(const std::string &path, const std::size_t &width, const std::size_t &height, char replacingChar)
{
    this->_sprite = std::make_unique<SimpleSprite>(path, width, height);
    this->_replacingChar = replacingChar;
    this->_color = std::make_unique<RGBAColor>(255, 255, 255, 255);
}

const ISprite &AEntity::getSprite() const
{
    return *this->_sprite;
}

void AEntity::setSprite(const ISprite &sprite)
{
    this->_sprite = std::make_unique<SimpleSprite>(sprite);
}


void AEntity::setSprite(std::unique_ptr<ISprite> sprite)
{
    this->_sprite = std::move(sprite);
}
