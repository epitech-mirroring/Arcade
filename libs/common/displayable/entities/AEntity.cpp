/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/entities/AEntity.hpp"
#include "common/displayable/entities/SimpleSprite.hpp"

AEntity::AEntity(std::unique_ptr<ISprite> sprite)
{
    this->_sprite = std::move(sprite);
}

AEntity::AEntity(const std::string &path)
{
    this->_sprite = std::make_unique<SimpleSprite>(path);
}

const ISprite &AEntity::getSprite() const
{
    return *this->_sprite;
}

void AEntity::setSprite(const ISprite &sprite)
{
    this->_sprite = std::make_unique<SimpleSprite>(sprite.getPicture().getPath());
}


void AEntity::setSprite(std::unique_ptr<ISprite> sprite)
{
    this->_sprite = std::move(sprite);
}
