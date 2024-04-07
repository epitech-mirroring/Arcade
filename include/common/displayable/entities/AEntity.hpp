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
    /**
     * @brief Construct a new AEntity object
     * @param sprite The sprite of the entity
     * @param replacingChar The character that will replace the entity (default: ' ')
     * @note The sprite ownership is transferred to the entity
     */
    AEntity(std::unique_ptr<ISprite> sprite, char replacingChar = ' ');
    /**
     * @brief Construct a new AEntity object
     * @param sprite The sprite of the entity
     * @param replacingChar The character that will replace the entity (default: ' ')
     * @note The sprite is copied
     */
    AEntity(const ISprite &sprite, char replacingChar = ' ');
    /**
     * @brief Construct a new AEntity object
     * @param path The path to the sprite
     * @param width The width of the entity
     * @param height The height of the entity
     * @param replacingChar The character that will replace the entity (default: ' ')
     * @note The sprite is loaded from the path
     */
    AEntity(const std::string &path, const std::size_t &width, const std::size_t &height, char replacingChar = ' ');
public:
    /**
     * @brief Destroy the AEntity object
     */
    ~AEntity() override = default;
    /**
     * @brief Get the sprite of the entity
     * @return The sprite of the entity
     */
    [[nodiscard]] const ISprite &getSprite() const override;
    /**
     * @brief Set the sprite of the entity
     * @param sprite The new sprite of the entity
     */
    void setSprite(const ISprite &sprite) override;
    /**
     * @brief Set the sprite of the entity
     * @param sprite The new sprite of the entity
     * @note The sprite ownership is transferred to the entity
     */
    void setSprite(std::unique_ptr<ISprite> sprite) override;
};
