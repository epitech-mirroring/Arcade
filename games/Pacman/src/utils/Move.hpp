/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../entities/APacManEntity.hpp"
#include "../entities/Wall.hpp"
#include "GridCoordinate.hpp"

class Move {
protected:
    GridCoordinate _from;
    GridCoordinate _to;
    Direction _direction;
    Direction _direction_;
    APacManEntity *_actor;
public:
    Move(const GridCoordinate &from, APacManEntity &actor, Direction direction);
    Move(const GridCoordinate &from, APacManEntity &actor, Direction direction, Direction _direction);
    ~Move() = default;

    void computeLanding();
    [[nodiscard]] bool isLegal(const Wall (&map)[37][28]) const;
    [[nodiscard]] const GridCoordinate &getTo() const;
    [[nodiscard]] Direction getDirection() const;
};
