/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once

#include "common/displayable/entities/AEntity.hpp"

class LevelCounter: public AEntity {
protected:
    std::size_t _level;
public:
    LevelCounter();
    ~LevelCounter() override = default;

    void setLevel(std::size_t level);
};
