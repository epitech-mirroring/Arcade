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
    Circle(std::unique_ptr<IColor> &color, std::size_t radius, char replacingChar = '*');
    Circle(const IColor &color, std::size_t radius, char replacingChar = '*');
    Circle(const ICircle &circle);
    Circle(const Circle &circle);
    ~Circle() override = default;
    [[nodiscard]] std::size_t getRadius() const override;
    void setRadius(std::size_t radius) override;
};

