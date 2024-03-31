/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "AEntity.hpp"

class SimpleEntity : public AEntity {
public:
    explicit SimpleEntity(std::unique_ptr<ISprite> sprite);
    explicit SimpleEntity(const std::string &path, const std::size_t &width, const std::size_t &height);
    ~SimpleEntity() override = default;
};
