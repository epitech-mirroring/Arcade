/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "APrimitive.hpp"
#include "shared/displayable/primitives/ILine.hpp"
#include "common/utils/RGBAColor.hpp"

class Line : public APrimitive, public ILine {
protected:
    std::unique_ptr<ICoordinate> _end;
public:
    Line(std::unique_ptr<ICoordinate> &end, std::unique_ptr<IColor> &color, char replacingChar = '*');
    Line(const ICoordinate &end, const IColor &color, char replacingChar = '*');
    explicit Line(const ICoordinate &end, const RGBAColor &color = RGBAColor::WHITE, char replacingChar = '*');
    Line(const ILine &line);
    Line(const Line &line);
    ~Line() override = default;
    [[nodiscard]] const ICoordinate &getEnd() const override;
    void setEnd(const ICoordinate &end) override;
    void setEnd(std::unique_ptr<ICoordinate> end) override;
};
