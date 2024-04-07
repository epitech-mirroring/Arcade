/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "GridCoordinate.hpp"
#include "../PacmanGlobals.hpp"
#include <cmath>

GridCoordinate::GridCoordinate(int x, int y, state state)
    : Coord2D(x, y), _state(state)
{
}

GridCoordinate::GridCoordinate(std::size_t x, std::size_t y, state state)
    : Coord2D((int) x, (int) y), _state(state)
{
}

GridCoordinate::GridCoordinate(const ICoordinate &coord, state state)
    : Coord2D(coord.getX(), coord.getY()), _state(state)
{
}

GridCoordinate::GridCoordinate(const GridCoordinate &coord) = default;

GridCoordinate &GridCoordinate::toScreen()
{
    if (_state == GRID) {
        _state = SCREEN;
        _x = (int) ((float) _x * 8.f * SCALE);
        _y = (int) ((float) _y * 8.f * SCALE);
    } else {
        throw std::runtime_error("GridCoordinate is already in screen state");
    }
    return *this;
}

GridCoordinate &GridCoordinate::toGrid()
{
    if (_state == SCREEN) {
        _state = GRID;
        _x = (int) ((float) _x / 8.f / SCALE);
        _y = (int) ((float) _y / 8.f / SCALE);
    } else {
        throw std::runtime_error("GridCoordinate is already in grid state");
    }
    return *this;
}

GridCoordinate &GridCoordinate::round()
{
    if (_state == SCREEN) {
        this->toGrid();
        this->toScreen();
    } else {
        this->toScreen();
        this->toGrid();
    }
    return *this;
}

bool GridCoordinate::operator==(const GridCoordinate &coord) const
{
    if (_state != coord._state)
        return false;
    if (_x != coord._x)
        return false;
    if (_y != coord._y)
        return false;
    return true;
}

GridCoordinate &GridCoordinate::operator=(const GridCoordinate &coord)
{
    _x = coord._x;
    _y = coord._y;
    _state = coord._state;
    return *this;
}

double GridCoordinate::distance(const GridCoordinate &coord) const
{
    if (_state != coord._state)
        return -1;
    return sqrt(pow(coord._x - _x, 2) + pow(coord._y - _y, 2));
}
