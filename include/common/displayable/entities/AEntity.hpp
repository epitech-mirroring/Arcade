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

class AEntity : public virtual ADisplayable, public virtual IEntity {
protected:
    std::unique_ptr<ISprite> _sprite;
    AEntity(std::unique_ptr<ISprite> sprite);
    AEntity(const std::string &path);
public:
    ~AEntity() override= default;
    [[nodiscard]] const std::unique_ptr<ISprite> &getSprite() const override;
    void setSprite(ISprite &sprite) override;
};
