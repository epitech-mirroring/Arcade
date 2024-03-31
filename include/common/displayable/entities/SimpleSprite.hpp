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
    explicit SimpleSprite(const IPicture &picture);
    explicit SimpleSprite(std::unique_ptr<IPicture> picture);
    explicit SimpleSprite(const std::string &path, const std::size_t &width, const std::size_t &height);
    explicit SimpleSprite(const ISprite &sprite);
    ~SimpleSprite() override = default;

    [[nodiscard]] const IPicture &getPicture() const override;
    void setPicture(std::unique_ptr<IPicture> picture) override;
    void setPicture(const IPicture &picture) override;
};
