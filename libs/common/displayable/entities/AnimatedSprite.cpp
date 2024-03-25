/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/entities/AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(std::unique_ptr<IPicture> picture, size_t nbFrames, size_t frameDuration)
{
    _picture = std::move(picture);
    _nbFrames = nbFrames;
    _frameDuration = frameDuration;
    _currentFrame = 0;
    _currentDuration = 0;
}

const std::unique_ptr<IPicture> &AnimatedSprite::getPicture() const
{
    return _picture;
}

void AnimatedSprite::setPicture(std::unique_ptr<IPicture> picture)
{
    _picture = std::move(picture);
}

void AnimatedSprite::update()
{
    _currentDuration++;
    if (_currentDuration >= _frameDuration) {
        _currentDuration = 0;
        _currentFrame++;
        if (_currentFrame >= _nbFrames)
            _currentFrame = 0;
    }
}

size_t AnimatedSprite::getCurrentFrame() const
{
    return _currentFrame;
}

size_t AnimatedSprite::getNbFrames() const
{
    return _nbFrames;
}

size_t AnimatedSprite::getFrameDuration() const
{
    return _frameDuration;
}
