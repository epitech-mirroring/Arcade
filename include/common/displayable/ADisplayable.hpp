/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../shared/displayable/IDisplayable.hpp"
#include "../../shared/utils/ICanRotate.hpp"
#include "common/utils/RGBAColor.hpp"
#include <cstddef>
#include <memory>
#include <cmath>

#define IS_INSTANCE_OF(type, obj) (dynamic_cast<type *>(&obj) != nullptr)
#define TRANSFORM_TO(type, obj) (dynamic_cast<type *>(&obj))

class ADisplayable : public virtual IDisplayable, public virtual ICanRotate {
protected:
    std::unique_ptr<ICoordinate> _position;
    std::unique_ptr<IColor> _color;
    float _size;
    float _rotation;
    char _replacingChar;
    /**
     * @brief Construct a new ADisplayable object
     * The position is set to (0, 0)
     * The size is set to 1
     * The rotation is set to 0
     * The replacing char is set to ' '
     * The color is set to white
     * The position is set to (0, 0)
     */
    ADisplayable();
public:
    /**
     * @brief Destroy the ADisplayable object
     */
    ~ADisplayable() override = default;
    /**
     * @brief Get the position of the displayable
     * @return The position of the displayable
     */
    [[nodiscard]] const ICoordinate &getPosition() const override;
    /**
     * @brief Get the size of the displayable
     * @return The size of the displayable
     */
    [[nodiscard]] float getSize() const override;
    /**
     * @brief Set the position of the displayable
     * @param position The new position of the displayable
     */
    void setPosition(const ICoordinate &position) override;
    /**
     * @brief Set the position of the displayable
     * @param position The new position of the displayable
     * @note The ownership of the pointer is transferred
     */
    void setPosition(std::unique_ptr<ICoordinate> position) override;
    /**
     * @brief Set the size of the displayable
     * @param size The new size of the displayable
     */
    void setSize(float size) override;
    /**
     * @brief Get the rotation of the displayable
     * @return The rotation of the displayable
     */
    [[nodiscard]] float getRotation() const override;
    /**
     * @brief Set the rotation of the displayable
     * @param angle The new rotation of the displayable
     */
    void setRotation(float angle) override;
    /**
     * @brief Get the replacing char of the displayable
     * @return The replacing char of the displayable
     */
    [[nodiscard]] char getReplacingChar() const override;
    /**
     * @brief Get the color of the displayable
     * @return The color of the displayable
     */
    [[nodiscard]] const IColor &getColor() const override;
    /**
     * @brief Set the color of the displayable
     * @param color The new color of the displayable
     */
    void setColor(const IColor &color) override;
    /**
     * @brief Set the color of the displayable
     * @param color The new color of the displayable
     * @note The ownership of the pointer is transferred
     */
    void setColor(std::unique_ptr<IColor> color) override;
};
