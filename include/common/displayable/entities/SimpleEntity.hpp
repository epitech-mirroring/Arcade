/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "AEntity.hpp"

class SimpleEntity : public AEntity {
public:
    /**
     * @brief Construct a new SimpleEntity object
     * @param sprite The sprite of the entity
     * @note The sprite ownership is transferred to the entity
     */
    explicit SimpleEntity(std::unique_ptr<ISprite> sprite);
    /**
     * @brief Construct a new SimpleEntity object
     * @param path The path to the sprite
     * @param width The width of the sprite
     * @param height The height of the sprite
     * @note The sprite is loaded from the path
     */
    explicit SimpleEntity(const std::string &path, const std::size_t &width, const std::size_t &height);
    /**
     * @brief Destroy the SimpleEntity object
     */
    ~SimpleEntity() override = default;
};
