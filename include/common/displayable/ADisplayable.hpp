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

class ADisplayable : public IDisplayable, public ICanRotate {
protected:
    std::unique_ptr<ICoordinate> _position;
    int _size;
    float _rotation;
    ADisplayable();
public:
    ~ADisplayable() override = default;
    const std::unique_ptr<ICoordinate> &getPosition() const override;
    int getSize() const override;
    void setPosition(ICoordinate &position) override;
    void setSize(int size) override;
    float getRotation() const override;
    void setRotation(float angle) override;
};
