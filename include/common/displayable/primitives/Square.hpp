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
    std::size_t _width;
    std::size_t _height;
public:
    Square(std::unique_ptr<IColor> &color, size_t width, std::size_t height);
    Square(const IColor &color, size_t width, std::size_t height);
    ~Square() override = default;
    [[nodiscard]] std::size_t getWidth() const override;
    [[nodiscard]] std::size_t getHeight() const override;
    void setWidth(std::size_t width) override;
    void setHeight(std::size_t height) override;
};

