/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/entities/SimpleEntity.hpp"

SimpleEntity::SimpleEntity(std::unique_ptr<ISprite> sprite): AEntity(std::move(sprite))
{
    this->_replacingChar = ' ';
}

SimpleEntity::SimpleEntity(const std::string &path, const std::size_t &width, const std::size_t &height): AEntity(path, width, height)
{
    this->_replacingChar = ' ';
}
