/*
** EPITECH PROJECT, 2024
** ArcadeShared
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/utils/Coord2D.hpp"
#include <cmath>

Coord2D::Coord2D(int x, int y)
{
    this->_x = x;
    this->_y = y;
}

Coord2D::Coord2D(const ICoordinate &coord)
{
    this->_x = coord.getX();
    this->_y = coord.getY();
}

Coord2D::Coord2D()
{
    this->_x = 0;
    this->_y = 0;
}

Coord2D::~Coord2D() = default;

int Coord2D::getX() const
{
    return this->_x;
}

int Coord2D::getY() const
{
    return this->_y;
}

void Coord2D::setX(int x)
{
    this->_x = x;
}

void Coord2D::setY(int y)
{
    this->_y = y;
}

void Coord2D::move(int x, int y)
{
    this->_x += x;
    this->_y += y;
}

void Coord2D::move(ICoordinate *coord)
{
    this->_x += coord->getX();
    this->_y += coord->getY();
}

double Coord2D::distance(const ICoordinate &coord) const
{
    return sqrt(pow(this->_x - coord.getX(), 2) + pow(this->_y - coord.getY(), 2));
}

// Operators

bool Coord2D::operator==(const Coord2D &coord) const
{
    return this->_x == coord.getX() && this->_y == coord.getY();
}

bool Coord2D::operator!=(const Coord2D &coord) const
{
    return !(*this == coord);
}

Coord2D &Coord2D::operator=(const Coord2D &coord)
{
    this->_x = coord.getX();
    this->_y = coord.getY();
    return *this;
}

Coord2D Coord2D::operator+(const Coord2D &coord) const
{
    return Coord2D(this->_x + coord.getX(), this->_y + coord.getY());
}

Coord2D Coord2D::operator-(const Coord2D &coord) const
{
    return Coord2D(this->_x - coord.getX(), this->_y - coord.getY());
}

Coord2D Coord2D::operator*(int value) const
{
    return Coord2D(this->_x * value, this->_y * value);
}

Coord2D Coord2D::operator/(int value) const
{
    return Coord2D(this->_x / value, this->_y / value);
}

Coord2D &Coord2D::operator+=(const Coord2D &coord)
{
    (*this) = (*this) + coord;
    return *this;
}

Coord2D &Coord2D::operator-=(const Coord2D &coord)
{
    (*this) = (*this) - coord;
    return *this;
}

Coord2D &Coord2D::operator*=(int value)
{
    (*this) = (*this) * value;
    return *this;
}

Coord2D &Coord2D::operator/=(int value)
{
    (*this) = (*this) / value;
    return *this;
}

bool Coord2D::operator<(const Coord2D &coord) const
{
    float d = sqrt(pow(this->_x, 2) + pow(this->_y, 2));
    float d2 = sqrt(pow(coord.getX(), 2) + pow(coord.getY(), 2));
    return d < d2;
}

bool Coord2D::operator>(const Coord2D &coord) const
{
    float d = sqrt(pow(this->_x, 2) + pow(this->_y, 2));
    float d2 = sqrt(pow(coord.getX(), 2) + pow(coord.getY(), 2));
    return d > d2;
}

bool Coord2D::operator<=(const Coord2D &coord) const
{
    float d = sqrt(pow(this->_x, 2) + pow(this->_y, 2));
    float d2 = sqrt(pow(coord.getX(), 2) + pow(coord.getY(), 2));
    return d <= d2;
}

bool Coord2D::operator>=(const Coord2D &coord) const
{
    float d = sqrt(pow(this->_x, 2) + pow(this->_y, 2));
    float d2 = sqrt(pow(coord.getX(), 2) + pow(coord.getY(), 2));
    return d >= d2;
}

std::ostream &operator<<(std::ostream &os, const Coord2D &coord)
{
    os << "(" << coord.getX() << ", " << coord.getY() << ")";
    return os;
}
