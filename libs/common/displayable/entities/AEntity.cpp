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
    _sprite = std::move(sprite);
}

AEntity::AEntity(const std::string &path)
{
    _sprite = std::make_unique<SimpleSprite>(path);
}

const std::unique_ptr<ISprite> &AEntity::getSprite() const
{
    return _sprite;
}

void AEntity::setSprite(ISprite &sprite)
{
    _sprite = std::unique_ptr<ISprite>(&sprite);
}
