/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/primitives/IPrimitive.hpp"
#include "../ADisplayable.hpp"

class APrimitive : public virtual ADisplayable, public virtual IPrimitive {
protected:
    std::unique_ptr<IColor> _color;
    explicit APrimitive(std::unique_ptr<IColor> &color, char replacingChar = '*');
    explicit APrimitive(const IColor &color, char replacingChar = '*');
public:
    ~APrimitive() override = default;
    [[nodiscard]] const IColor &getColor() const override;
    void setColor(const IColor &color) override;
    void setColor(std::unique_ptr<IColor> color) override;
};
