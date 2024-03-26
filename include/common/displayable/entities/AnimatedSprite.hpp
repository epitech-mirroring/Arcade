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
    size_t _nbFrames;
    size_t _currentFrame;
    size_t _frameDuration;
    size_t _currentDuration;
public:
    AnimatedSprite(std::unique_ptr<IPicture> picture, size_t nbFrames, size_t frameDuration);
    ~AnimatedSprite() = default;

    const std::unique_ptr<IPicture> &getPicture() const override;
    void setPicture(std::unique_ptr<IPicture> picture) override;
    void update();
    size_t getCurrentFrame() const;
    size_t getNbFrames() const;
    size_t getFrameDuration() const;
};
