/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/entities/ISprite.hpp"

class SimpleSprite : public ISprite {
protected:
    std::unique_ptr<IPicture> _picture;
public:
    explicit SimpleSprite(std::unique_ptr<IPicture> picture);
    explicit SimpleSprite(const std::string &path);
    ~SimpleSprite() override = default;

    [[nodiscard]] const std::unique_ptr<IPicture> &getPicture() const override;
    void setPicture(std::unique_ptr<IPicture> picture) override;
};
