/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/primitives/ISquare.hpp"
#include "APrimitive.hpp"
#include "../../utils/Coord2D.hpp"

class Square : public APrimitive, public ISquare {
protected:
    std::size_t _width;
    std::size_t _height;
    bool _isFilled;
public:
    /**
     * @brief Construct a new Square object
     * @param color The color of the square
     * @param width The width of the square
     * @param height The height of the square
     * @param isFilled If the square is filled or not (default: true)
     * @param replacingChar The character that will replace the square (default: '*')
     * @note The color ownership is transferred to the square
     */
    Square(std::unique_ptr<IColor> &color, size_t width, std::size_t height, bool isFilled = true, char replacingChar = '*');
    /**
     * @brief Construct a new Square object
     * @param color The color of the square
     * @param width The width of the square
     * @param height The height of the square
     * @param isFilled If the square is filled or not (default: true)
     * @param replacingChar The character that will replace the square (default: '*')
     * @note The color is copied
     */
    Square(const IColor &color, size_t width, std::size_t height, bool isFilled = true, char replacingChar = '*');
    /**
     * @brief Construct a new Square object
     * @param square The square to copy
     */
    Square(const ISquare &square);
    /**
     * @brief Construct a new Square object
     * @param square The square to copy
     */
    Square(const Square &square);
    /**
     * @brief Destroy the Square object
     */
    ~Square() override = default;
    /**
     * @brief Get the width of the square
     * @return The width of the square
     */
    [[nodiscard]] std::size_t getWidth() const override;
    /**
     * @brief Get the height of the square
     * @return The height of the square
     */
    [[nodiscard]] std::size_t getHeight() const override;
    /**
     * @brief Set the width of the square
     * @param width The new width of the square
     */
    void setWidth(std::size_t width) override;
    /**
     * @brief Set the height of the square
     * @param height The new height of the square
     */
    void setHeight(std::size_t height) override;
    /**
     * @brief Check if the square is filled
     * @return true If the square is filled, false otherwise
     */
    [[nodiscard]] bool isFilled() const override;
    /**
     * @brief Set if the square is filled
     * @param isFilled If the square is filled
     */
    void setIsFilled(bool isFilled) override;
};
