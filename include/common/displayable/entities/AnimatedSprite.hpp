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
    /**
     * @brief Construct a new Animated Sprite object
     * @param picture The picture of the sprite
     * @param nbFrames The number of frames of the sprite sheet
     * @param frameDuration The duration of a frame in ms
     * @note The picture ownership is transferred to the sprite
     */
    AnimatedSprite(std::unique_ptr<IPicture> picture, std::size_t nbFrames, std::size_t frameDuration);
    /**
     * @brief Construct a new Animated Sprite object
     * @param picture The picture of the sprite
     * @param nbFrames The number of frames of the sprite sheet
     * @param frameDuration The duration of a frame in ms
     */
    AnimatedSprite(const IPicture &picture, std::size_t nbFrames, std::size_t frameDuration);
    /**
     * @brief Destroy the Animated Sprite object
     */
    ~AnimatedSprite() override = default;

    /**
     * @brief Get the picture of the sprite
     * @return The picture of the sprite
     */
    [[nodiscard]] const IPicture &getPicture() const override;
    /**
     * @brief Set the picture of the sprite
     * @param picture The new picture of the sprite
     * @note The picture ownership is transferred to the sprite
     */
    void setPicture(std::unique_ptr<IPicture> picture) override;
    /**
     * @brief Set the picture of the sprite
     * @param picture The new picture of the sprite
     */
    void setPicture(const IPicture &picture) override;
    /**
     * @brief Update the sprite
     */
    void update();
    /**
     * @brief Get the current frame of the sprite
     * @return The current frame of the sprite
     */
    [[nodiscard]] std::size_t getCurrentFrame() const;
    /**
     * @brief Get the number of frames of the sprite
     * @return The number of frames of the sprite
     */
    [[nodiscard]] std::size_t getNbFrames() const;
    /**
     * @brief Get the duration of a frame of the sprite
     * @return The duration of a frame of the sprite
     */
    [[nodiscard]] std::size_t getFrameDuration() const;
    /**
     * @brief Get the draw rect of the sprite
     * @return The draw rect of the sprite
     */
    [[nodiscard]] const DrawRect &getDrawRect() const override;
    /**
     * @brief Set the draw rect of the sprite
     * @param drawRect The new draw rect of the sprite
     */
    void setDrawRect(const DrawRect &drawRect) override;
};
