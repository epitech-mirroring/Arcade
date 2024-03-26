/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/primitives/ISquare.hpp"
#include "APrimitive.hpp"
#include "../../utils/Coord2D.hpp"

class Square : public APrimitive, public ISquare {
protected:
    size_t _width;
    size_t _height;
public:
    Square(std::unique_ptr<IColor> color, size_t width, size_t height);
    ~Square() override = default;
    size_t getWidth() const override;
    size_t getHeight() const override;
    void setWidth(size_t width) override;
    void setHeight(size_t height) override;
};

