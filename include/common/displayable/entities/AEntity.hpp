/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/entities/IEntity.hpp"
#include "../ADisplayable.hpp"

class AEntity : public ADisplayable, public IEntity {
protected:
    std::unique_ptr<ISprite> _sprite;
    AEntity(std::unique_ptr<ISprite> sprite);
    AEntity(const std::string &path);

public:
    ~AEntity() = default;
    virtual const std::unique_ptr<ISprite> &getSprite() const override;
    virtual void setSprite(ISprite &sprite) override;
};
