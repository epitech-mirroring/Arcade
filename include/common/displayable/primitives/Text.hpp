/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../../../shared/displayable/primitives/IText.hpp"
#include "APrimitive.hpp"
#include <string>

class Text : public APrimitive, public IText {
protected:
    std::string _text;
    std::string _fontPath;
public:
    /**
     * @brief Construct a new Text object
     * @param color The color of the text
     * @param text The text to display (default: "")
     * @param fontPath The path to the font file (default: "assets/Arial.ttf")
     * @note The color ownership is transferred to the text
     */
    Text(std::unique_ptr<IColor> &color, const std::string &text = "", const std::string &fontPath = "assets/Arial.ttf");
    /**
     * @brief Construct a new Text object
     * @param color The color of the text
     * @param text The text to display (default: "")
     * @param fontPath The path to the font file (default: "assets/Arial.ttf")
     */
    Text(const IColor &color, const std::string &text = "", const std::string &fontPath = "assets/Arial.ttf");
    /**
     * @brief Destroy the Text object
     */
    ~Text() override = default;
    /**
     * @brief Get the text of the text
     * @return The text of the text
     */
    [[nodiscard]] const std::string &getText() const override;
    /**
     * @brief Set the text of the text
     * @param text The new text of the text
     */
    void setText(const std::string &text) override;
    /**
     * @brief Get the path to the font file
     * @return The path to the font file
     */
    [[nodiscard]] const std::string &getFontPath() const override;
};
