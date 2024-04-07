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
    DrawRect _drawRect;
public:
    /**
     * @brief Construct a new Simple Sprite object
     * @param picture The picture of the sprite
     * @note The picture is copied
     */
    explicit SimpleSprite(const IPicture &picture);
    /**
     * @brief Construct a new Simple Sprite object
     * @param picture The picture of the sprite
     * @note The picture ownership is transferred to the sprite
     * A new sprite is created with the picture
     */
    explicit SimpleSprite(std::unique_ptr<IPicture> picture);
    /**
     * @brief Construct a new Simple Sprite object
     * @param path The path to the sprite
     * @param width The width of the sprite
     * @param height The height of the sprite
     * @note The sprite is loaded from the path
     */
    explicit SimpleSprite(const std::string &path, const std::size_t &width, const std::size_t &height);
    /**
     * @brief Destroy the Simple Sprite object
     * @param sprite
     */
    explicit SimpleSprite(const ISprite &sprite);
    /**
     * @brief Destroy the Simple Sprite object
     */
    ~SimpleSprite() override = default;

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
