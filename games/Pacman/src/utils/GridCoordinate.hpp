/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/utils/Coord2D.hpp"


class GridCoordinate: public Coord2D {
public:
    enum state {
        GRID,
        SCREEN
    };

    GridCoordinate(int x, int y, state state = GRID);
    GridCoordinate(std::size_t x, std::size_t y, state state = GRID);
    GridCoordinate(const GridCoordinate &coord);
    GridCoordinate(const ICoordinate &coord, state state);

    [[nodiscard]] double distance(const GridCoordinate &coord) const;

    GridCoordinate &toScreen();
    GridCoordinate &toGrid();
    GridCoordinate &round();

    bool operator== (const GridCoordinate &coord) const;
    GridCoordinate &operator= (const GridCoordinate &coord);
protected:
    state _state;
};
