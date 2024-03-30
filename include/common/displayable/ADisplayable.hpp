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
    int _size;
    float _rotation;
    ADisplayable();
public:
    ~ADisplayable() override = default;
    [[nodiscard]] const ICoordinate &getPosition() const override;
    [[nodiscard]] int getSize() const override;
    void setPosition(const ICoordinate &position) override;
    void setPosition(std::unique_ptr<ICoordinate> position) override;
    void setSize(int size) override;
    [[nodiscard]] float getRotation() const override;
    void setRotation(float angle) override;
};
