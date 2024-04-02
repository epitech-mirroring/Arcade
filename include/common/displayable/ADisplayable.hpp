/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../shared/displayable/IDisplayable.hpp"
#include "../../shared/utils/ICanRotate.hpp"
#include <cstddef>
#include <memory>
#include <cmath>

#define IS_INSTANCE_OF(type, obj) (dynamic_cast<type *>(&obj) != nullptr)
#define TRANSFORM_TO(type, obj) (dynamic_cast<type *>(&obj))

class ADisplayable : public virtual IDisplayable, public virtual ICanRotate {
protected:
    std::unique_ptr<ICoordinate> _position;
    float _size;
    float _rotation;
    char _replacingChar;
    ADisplayable();
public:
    ~ADisplayable() override = default;
    [[nodiscard]] const ICoordinate &getPosition() const override;
    [[nodiscard]] float getSize() const override;
    void setPosition(const ICoordinate &position) override;
    void setPosition(std::unique_ptr<ICoordinate> position) override;
    void setSize(float size) override;
    [[nodiscard]] float getRotation() const override;
    void setRotation(float angle) override;
    [[nodiscard]] char getReplacingChar() const override;
};
