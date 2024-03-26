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
    virtual const std::unique_ptr<ICoordinate> &getPosition() const override;
    virtual int getSize() const override;
    virtual void setPosition(ICoordinate &position) override;
    virtual void setSize(int size) override;
    virtual float getRotation() const override;
    virtual void setRotation(float angle) override;
};
