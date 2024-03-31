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
public:
    Text(std::unique_ptr<IColor> &color, const std::string &text = "", const std::string &fontPath = "assets/Arial.ttf");
    Text(const IColor &color, const std::string &text = "", const std::string &fontPath = "assets/Arial.ttf");
    ~Text() override = default;
    [[nodiscard]] const std::string &getText() const override;
    void setText(const std::string &text) override;
    [[nodiscard]] const std::string &getFontPath() const override;
};
