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

class APrimitive : public ADisplayable, public IPrimitive {
protected:
    std::unique_ptr<IColor> _color;
    APrimitive(std::unique_ptr<IColor> color);
public:
    ~APrimitive() override = default;
    const std::unique_ptr<IColor> &getColor() const override;
};
