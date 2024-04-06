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
    AEntity(std::unique_ptr<ISprite> sprite, char replacingChar = ' ');
    AEntity(const ISprite &sprite, char replacingChar = ' ');
    AEntity(const std::string &path, const std::size_t &width, const std::size_t &height, char replacingChar = ' ');
public:
    ~AEntity() override = default;
    [[nodiscard]] const ISprite &getSprite() const override;
    void setSprite(const ISprite &sprite) override;
    void setSprite(std::unique_ptr<ISprite> sprite) override;
};
