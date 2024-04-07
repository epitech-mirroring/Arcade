/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "APrimitive.hpp"
#include "shared/displayable/primitives/ILine.hpp"
#include "common/utils/RGBAColor.hpp"

class Line : public APrimitive, public ILine {
protected:
    std::unique_ptr<ICoordinate> _end;
public:
    /**
     * @brief Construct a new Line object
     * @param end The end of the line
     * @param color The color of the line
     * @param replacingChar The character that will replace the line (default: '*')
     * @note The color and the end coordinate ownership is transferred to the line
     */
    Line(std::unique_ptr<ICoordinate> &end, std::unique_ptr<IColor> &color, char replacingChar = '*');
    /**
     * @brief Construct a new Line object
     * @param end The end of the line
     * @param color The color of the line
     * @param replacingChar The character that will replace the line (default: '*')
     */
    Line(const ICoordinate &end, const IColor &color, char replacingChar = '*');
    /**
     * @brief Construct a new Line object
     * @param end The end of the line
     * @param color The color of the line (default: white)
     * @param replacingChar The character that will replace the line (default: '*')
     * @note The color is copied
     */
    explicit Line(const ICoordinate &end, const RGBAColor &color = RGBAColor::WHITE, char replacingChar = '*');
    /**
     * @brief Construct a new Line object
     * @param line The line to copy
     */
    Line(const ILine &line);
    /**
     * @brief Construct a new Line object
     * @param line The line to copy
     */
    Line(const Line &line);
    /**
     * @brief Destroy the Line object
     */
    ~Line() override = default;
    /**
     * @brief Get the end of the line
     * @return The end of the line
     */
    [[nodiscard]] const ICoordinate &getEnd() const override;
    /**
     * @brief Set the end of the line
     * @param end The new end of the line
     */
    void setEnd(const ICoordinate &end) override;
    /**
     * @brief Set the end of the line
     * @param end The new end of the line
     * @note The ownership of the pointer is transferred
     */
    void setEnd(std::unique_ptr<ICoordinate> end) override;
};
