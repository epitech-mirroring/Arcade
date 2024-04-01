/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/entities/ISprite.hpp"
#include <cstddef>

class AnimatedSprite : public ISprite {
protected:
    std::unique_ptr<IPicture> _picture;
    std::size_t _nbFrames;
    std::size_t _currentFrame;
    std::size_t _frameDuration;
    std::size_t _currentDuration;
    DrawRect _drawRect;
public:
    AnimatedSprite(std::unique_ptr<IPicture> picture, std::size_t nbFrames, std::size_t frameDuration);
    AnimatedSprite(const IPicture &picture, std::size_t nbFrames, std::size_t frameDuration);
    ~AnimatedSprite() override = default;

    [[nodiscard]]  const IPicture &getPicture() const override;
    void setPicture(std::unique_ptr<IPicture> picture) override;
    void setPicture(const IPicture &picture) override;
    void update();
    [[nodiscard]] std::size_t getCurrentFrame() const;
    [[nodiscard]] std::size_t getNbFrames() const;
    [[nodiscard]] std::size_t getFrameDuration() const;
    [[nodiscard]] const DrawRect &getDrawRect() const override;
    void setDrawRect(const DrawRect &drawRect) override;
};
