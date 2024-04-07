/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/primitives/ICircle.hpp"
#include "APrimitive.hpp"
#include "../../utils/Coord2D.hpp"

class Circle : public APrimitive, public ICircle {
protected:
    std::size_t _radius;
public:
    /**
     * @brief Construct a new Circle object
     * @param color The color of the circle
     * @param radius The radius of the circle
     * @param replacingChar The character that will replace the circle (default: '*')
     * @note The color ownership is transferred to the circle
     */
    Circle(std::unique_ptr<IColor> &color, std::size_t radius, char replacingChar = '*');
    /**
     * @brief Construct a new Circle object
     * @param color The color of the circle
     * @param radius The radius of the circle
     * @param replacingChar The character that will replace the circle (default: '*')
     * @note The color is copied
     */
    Circle(const IColor &color, std::size_t radius, char replacingChar = '*');
    /**
     * @brief Construct a new Circle object
     * @param circle The circle to copy
     */
    Circle(const ICircle &circle);
    /**
     * @brief Construct a new Circle object
     * @param circle The circle to copy
     */
    Circle(const Circle &circle);
    /**
     * @brief Destroy the Circle object
     */
    ~Circle() override = default;
    /**
     * @brief Get the radius of the circle
     * @return The radius of the circle
     */
    [[nodiscard]] std::size_t getRadius() const override;
    /**
     * @brief Set the radius of the circle
     * @param radius The new radius of the circle
     */
    void setRadius(std::size_t radius) override;
};

