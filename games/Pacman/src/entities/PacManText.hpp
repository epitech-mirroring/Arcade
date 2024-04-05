/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/displayable/entities/AEntity.hpp"
#include <vector>

enum PacManTextColor {
    WHITE = 0,
    RED = 4*8,
    PINK = 2 * 4*8,
    CYAN = 3 * 4*8,
    ORANGE = 4 * 4*8,
    BEIGE = 5 * 4*8,
    YELLOW = 6 * 4*8,
};

class PacManTextChar: public AEntity {
public:
    explicit PacManTextChar(char c, PacManTextColor color = WHITE);
};

class PacManText {
protected:
    std::vector<PacManTextChar *> _text;
    std::string _string;
    PacManTextColor _color;
public:
    explicit PacManText(const std::string &text, PacManTextColor color = WHITE);
    ~PacManText();

    void setText(const std::string &text);
    void setColor(PacManTextColor color);
    void setPosition(const ICoordinate &pos);

    [[nodiscard]] const std::vector<PacManTextChar *> &getChars() const;
};
