/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** Apple
*/

#pragma once

#include "common/displayable/entities/AEntity.hpp"
#include "common/utils/Coord2D.hpp"

class Apple : public AEntity {
public:
    Apple(int x, int y);
    Apple(const Coord2D &pos);
    ~Apple();
    Coord2D getPos() const;

private:
    Coord2D pos;
};
