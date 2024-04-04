/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/displayable/entities/AEntity.hpp"
#include "../PacmanGlobals.hpp"

class Wall : public AEntity {
public:
    enum WallType {
        CORNER_DOWN_LEFT = 0,
        CORNER_DOWN_RIGHT = 1,
        STRAIGHT_VERTICAL_RIGHT = 2,
        STRAIGHT_VERTICAL_LEFT = 3,
        CORNER_UP_LEFT = 4,
        CORNER_UP_RIGHT = 5,
        T_CORNER_RIGHT_UP_LEFT = 6,
        T_CORNER_LEFT_UP_RIGHT = 7,
        T_CORNER_RIGHT_DOWN_LEFT = 8,
        T_CORNER_LEFT_DOWN_RIGHT = 9,
        STRAIGHT_HORIZONTAL_UP = 10,
        STRAIGHT_HORIZONTAL_DOWN = 12,
        SIMPLE_STRAIGHT_HORIZONTAL_DOWN = 14,
        LONG_CORNER_UP_LEFT = 16,
        LONG_CORNER_UP_RIGHT = 17,
        LONG_CORNER_DOWN_LEFT = 18,
        LONG_CORNER_DOWN_RIGHT = 19,
        SIMPLE_STRAIGHT_HORIZONTAL_UP = 20,
        SHORT_CORNER_DOWN_LEFT = 22,
        SHORT_CORNER_DOWN_RIGHT = 23,
        SIMPLE_STRAIGHT_VERTICAL_LEFT = 24,
        SIMPLE_STRAIGHT_VERTICAL_RIGHT = 25,
        SHORT_CORNER_UP_LEFT = 26,
        SHORT_CORNER_UP_RIGHT = 27,
        SQUARE_CORNER_DOWN_LEFT = 28,
        SQUARE_CORNER_DOWN_RIGHT = 29,
        SQUARE_CORNER_UP_LEFT = 30,
        SQUARE_CORNER_UP_RIGHT = 31,
        STRAIGHT_HORIZONTAL_CAPPED_LEFT = 32,
        STRAIGHT_HORIZONTAL_CAPPED_RIGHT = 33,
        SIMPLE_CORNER_DOWN_RIGHT = 34,
        SIMPLE_CORNER_DOWN_LEFT = 35,
        SIMPLE_CORNER_UP_RIGHT = 36,
        SIMPLE_CORNER_UP_LEFT = 37,
        T_CORNER_UP_DOWN_RIGHT = 42,
        T_CORNER_UP_DOWN_LEFT = 43,
        EMPTY = 44,
        GATE = 46,
    };

    explicit Wall(WallType type, bool isWhite = false);
    ~Wall() override = default;

    [[nodiscard]] WallType getType() const;
    [[nodiscard]] bool isWhite() const;
private:
    WallType _type;
    bool _isWhite;
};
