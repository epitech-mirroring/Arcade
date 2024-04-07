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
    /**
     * @brief Construct a new Coord2D object
     * @param x the x position
     * @param y the y position
     */
    Coord2D(int x, int y);
    /**
     * @brief Construct a new Coord2D object from an ICoordinate object
     * @param coord the ICoordinate object to copy
     */
    Coord2D(const ICoordinate &coord);
    /**
     * @brief Construct a new Coord2D object (0, 0)
     */
    Coord2D();
    /**
     * @brief Destroy the Coord2D object
     */
    ~Coord2D() override;
    /**
     * @brief Get the x position
     * @return The x position
     */
    [[nodiscard]] int getX() const override;
    /**
     * @brief Get the y position
     * @return The y position
     */
    [[nodiscard]] int getY() const override;
    /**
     * @brief Set the x position
     * @param x The new x position
     */
    void setX(int x) override;
    /**
     * @brief Set the y position
     * @param y The new y position
     */
    void setY(int y) override;
    /**
     * @brief Move the coordinate
     * @param x The x offset
     * @param y The y offset
     */
    void move(int x, int y);
    /**
     * @brief Move the coordinate
     * @param coord The ICoordinate object to move with
     */
    void move(ICoordinate *coord);
    /**
     * @brief Get the distance between this coordinate and another
     * @param coord The other coordinate
     * @return The distance between the two coordinates
     * @note Uses the Pythagorean theorem
     */
    [[nodiscard]] double distance(const ICoordinate &coord) const;

    // Operators
    /**
     * @brief Compare two Coord2D objects
     * @param coord The Coord2D object to compare with
     * @return true if the x and y positions are the same, false otherwise
     */
    bool operator==(const Coord2D &coord) const;
    /**
     * @brief Compare two Coord2D objects
     * @param coord The Coord2D object to compare with
     * @return false if the x and y positions are the same, true otherwise
     */
    bool operator!=(const Coord2D &coord) const;
    /**
     * @brief Assign a Coord2D object to another
     * @param coord The Coord2D object to assign
     * @return The new Coord2D object
     */
    Coord2D &operator=(const Coord2D &coord);
    /**
     * @brief Add two Coord2D objects
     * @param coord The Coord2D object to add
     * @return The result of the addition
     */
    Coord2D operator+(const Coord2D &coord) const;
    /**
     * @brief Subtract two Coord2D objects
     * @param coord The Coord2D object to subtract
     * @return The result of the subtraction
     */
    Coord2D operator-(const Coord2D &coord) const;
    /**
     * @brief Multiply a Coord2D object by a value
     * @param value The value to multiply
     * @return The result of the multiplication
     */
    Coord2D operator*(int value) const;
    /**
     * @brief Divide a Coord2D object by a value
     * @param value The value to divide
     * @return The result of the division
     */
    Coord2D operator/(int value) const;
    /**
     * @brief Add a Coord2D object to this one
     * @param coord The Coord2D object to add
     * @return The new Coord2D object
     */
    Coord2D &operator+=(const Coord2D &coord);
    /**
     * @brief Subtract a Coord2D object to this one
     * @param coord The Coord2D object to subtract
     * @return The new Coord2D object
     */
    Coord2D &operator-=(const Coord2D &coord);
    /**
     * @brief Multiply this Coord2D object by a value
     * @param value The value to multiply
     * @return The new Coord2D object
     */
    Coord2D &operator*=(int value);
    /**
     * @brief Divide this Coord2D object by a value
     * @param value The value to divide
     * @return The new Coord2D object
     */
    Coord2D &operator/=(int value);
    /**
     * @brief Compare two Coord2D objects
     * @param coord The Coord2D object to compare with
     * @return true if the distance to the origin is smaller, false otherwise
     */
    bool operator<(const Coord2D &coord) const;
    /**
     * @brief Compare two Coord2D objects
     * @param coord The Coord2D object to compare with
     * @return true if the distance to the origin is greater, false otherwise
     */
    bool operator>(const Coord2D &coord) const;
    /**
     * @brief Compare two Coord2D objects
     * @param coord The Coord2D object to compare with
     * @return true if the distance to the origin is smaller or equal, false otherwise
     */
    bool operator<=(const Coord2D &coord) const;
    /**
     * @brief Compare two Coord2D objects
     * @param coord The Coord2D object to compare with
     * @return true if the distance to the origin is greater or equal, false otherwise
     */
    bool operator>=(const Coord2D &coord) const;
    /**
     * @brief Output the Coord2D object to an ostream
     * @param os The ostream object
     * @param coord The Coord2D object to output
     * @return The ostream object
     */
    friend std::ostream &operator<<(std::ostream &os, const Coord2D &coord);
};
