/*
** EPITECH PROJECT, 2024
** ArcadeShared
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../shared/utils/ICoordinate.hpp"
#include <ostream>

class Coord2D: public ICoordinate {
protected:
    int _x;
    int _y;
public:
    Coord2D(int x, int y);
    Coord2D(const ICoordinate &coord);
    Coord2D();
    ~Coord2D();
    int getX() const override;
    int getY() const override;
    void setX(int x) override;
    void setY(int y) override;
    void move(int x, int y);
    void move(ICoordinate *coord);

    // Operators
    bool operator==(const Coord2D &coord) const;
    bool operator!=(const Coord2D &coord) const;
    Coord2D &operator=(const Coord2D &coord);
    Coord2D operator+(const Coord2D &coord) const;
    Coord2D operator-(const Coord2D &coord) const;
    Coord2D operator*(int value) const;
    Coord2D operator/(int value) const;
    Coord2D &operator+=(const Coord2D &coord);
    Coord2D &operator-=(const Coord2D &coord);
    Coord2D &operator*=(int value);
    Coord2D &operator/=(int value);
    bool operator<(const Coord2D &coord) const;
    bool operator>(const Coord2D &coord) const;
    bool operator<=(const Coord2D &coord) const;
    bool operator>=(const Coord2D &coord) const;
    friend std::ostream &operator<<(std::ostream &os, const Coord2D &coord);
};
