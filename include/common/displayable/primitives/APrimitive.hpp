/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/primitives/IPrimitive.hpp"
#include "../ADisplayable.hpp"

class APrimitive : public virtual ADisplayable, public virtual IPrimitive {
protected:
    /**
     * @brief The color of the primitive
     * @param color The color of the primitive
     * @param replacingChar The character that will replace the primitive (default: '*')
     * @note The color ownership is transferred to the primitive
     */
    explicit APrimitive(std::unique_ptr<IColor> &color, char replacingChar = '*');
    /**
     * @brief The color of the primitive
     * @param color The color of the primitive
     * @param replacingChar The character that will replace the primitive (default: '*')
     * @note The color is copied
     */
    explicit APrimitive(const IColor &color, char replacingChar = '*');
public:
    /**
     * @brief Destroy the APrimitive object
     */
    ~APrimitive() override = default;
};
