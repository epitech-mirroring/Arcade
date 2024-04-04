/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/utils/Coord2D.hpp"
#include "../entities/APacManEntity.hpp"
#include "../PacmanGlobals.hpp"
#include "../entities/Wall.hpp"

class Move {
protected:
    Coord2D _from;
    Coord2D _to;
    Direction _direction;
    Direction _direction_;
    APacManEntity *_actor;
public:
    Move(const Coord2D &from, APacManEntity &actor, Direction direction);
    Move(const Coord2D &from, APacManEntity &actor, Direction direction, Direction _direction);
    ~Move() = default;

    void computeLanding();
    [[nodiscard]] bool isLegal(const Wall (&map)[37][28]) const;
    [[nodiscard]] const Coord2D &getTo() const;
};
