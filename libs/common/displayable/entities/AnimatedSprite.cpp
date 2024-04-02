/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/displayable/entities/AnimatedSprite.hpp"
#include "common/utils/Picture.hpp"

AnimatedSprite::AnimatedSprite(std::unique_ptr<IPicture> picture, std::size_t nbFrames, std::size_t frameDuration)
{
    this->_picture = std::move(picture);
    this->_nbFrames = nbFrames;
    this->_frameDuration = frameDuration;
    this->_currentFrame = 0;
    this->_currentDuration = 0;
    this->_drawRect = {0, 0, this->_picture->getWidth() / this->_nbFrames, this->_picture->getHeight()};
}

AnimatedSprite::AnimatedSprite(const IPicture &picture, std::size_t nbFrames, std::size_t frameDuration)
{
    this->_picture = std::make_unique<Picture>(picture);
    this->_nbFrames = nbFrames;
    this->_frameDuration = frameDuration;
    this->_currentFrame = 0;
    this->_currentDuration = 0;
    this->_drawRect = {0, 0, this->_picture->getWidth() / this->_nbFrames, this->_picture->getHeight()};
}

const IPicture &AnimatedSprite::getPicture() const
{
    return *this->_picture;
}

void AnimatedSprite::setPicture(std::unique_ptr<IPicture> picture)
{
    this->_picture = std::move(picture);
}

void AnimatedSprite::setPicture(const IPicture &picture)
{
    this->_picture = std::make_unique<Picture>(picture);
}

void AnimatedSprite::update()
{
    this->_currentDuration++;
    if (this->_currentDuration >= this->_frameDuration) {
        this->_currentDuration = 0;
        this->_currentFrame++;
        if (this->_currentFrame >= this->_nbFrames)
            this->_currentFrame = 0;
    }
    this->_drawRect.x = this->_currentFrame * this->_drawRect.width;
}

std::size_t AnimatedSprite::getCurrentFrame() const
{
    return this->_currentFrame;
}

std::size_t AnimatedSprite::getNbFrames() const
{
    return this->_nbFrames;
}

std::size_t AnimatedSprite::getFrameDuration() const
{
    return this->_frameDuration;
}

const DrawRect &AnimatedSprite::getDrawRect() const
{
    return this->_drawRect;
}

void AnimatedSprite::setDrawRect(const DrawRect &drawRect)
{
    this->_drawRect = drawRect;
}
