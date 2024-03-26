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
    size_t _radius;
public:
    Circle(std::unique_ptr<IColor> color, size_t radius);
    ~Circle() override = default;
    size_t getRadius() const override;
    void setRadius(size_t radius) override;
};

