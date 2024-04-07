/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "PacManText.hpp"
#include "../PacmanGlobals.hpp"
#include <map>

PacManTextChar::PacManTextChar(char c, PacManTextColor color)
    : AEntity("assets/games/pacman/text.png", 128, 224)
{
    static const std::map<char, std::pair<std::size_t, std::size_t>> charMap = {
        {'A', {0, 0}},
        {'B', {8, 0}},
        {'C', {16, 0}},
        {'D', {24, 0}},
        {'E', {32, 0}},
        {'F', {40, 0}},
        {'G', {48, 0}},
        {'H', {56, 0}},
        {'I', {64, 0}},
        {'J', {72, 0}},
        {'K', {80, 0}},
        {'L', {88, 0}},
        {'M', {96, 0}},
        {'N', {104, 0}},
        {'O', {112, 0}},
        {'P', {0, 8}},
        {'Q', {8, 8}},
        {'R', {16, 8}},
        {'S', {24, 8}},
        {'T', {32, 8}},
        {'U', {40, 8}},
        {'V', {48, 8}},
        {'W', {56, 8}},
        {'X', {64, 8}},
        {'Y', {72, 8}},
        {'Z', {80, 8}},
        {'!', {88, 8}},
        {'c', {96, 8}},
        {'p', {104, 8}},
        {'t', {112, 8}},
        {'0', {0, 16}},
        {'1', {8, 16}},
        {'2', {16, 16}},
        {'3', {24, 16}},
        {'4', {32, 16}},
        {'5', {40, 16}},
        {'6', {48, 16}},
        {'7', {56, 16}},
        {'8', {64, 16}},
        {'9', {72, 16}},
        {'/', {80, 16}},
        {'-', {88, 16}},
        {'"', {96, 16}},
        {' ', {104, 16}},
    };
    std::pair<std::size_t, std::size_t> pos = charMap.at(c);
    this->_sprite->setDrawRect({pos.first, pos.second + color, 8, 8});
    this->setSize(SCALE);
    this->_replacingChar = c;
    this->setColor(RGBAColor::WHITE);
}

PacManText::PacManText(const std::string &text, PacManTextColor color)
    : _string{text}, _color{color}
{
    for (char c : text) {
        this->_text.emplace_back(new PacManTextChar(c, color));
    }
}

PacManText::~PacManText()
{
    for (auto &c : this->_text) {
        delete c;
    }
}

void PacManText::setText(const std::string &text)
{
    this->_string = text;
    for (auto &c : this->_text) {
        delete c;
    }
    this->_text.clear();
    for (char c : text) {
        this->_text.emplace_back(new PacManTextChar(c, this->_color));
    }
}

void PacManText::setColor(PacManTextColor color)
{
    this->_color = color;
    for (auto &c : this->_text) {
        delete c;
    }
    this->_text.clear();
    for (char c : this->_string) {
        this->_text.emplace_back(new PacManTextChar(c, color));
    }
}

const std::vector<PacManTextChar *> &PacManText::getChars() const
{
    return this->_text;
}

void PacManText::setPosition(const ICoordinate &pos)
{
    std::size_t i = 0;
    for (auto &c : this->_text) {
        GridCoordinate newPos = GridCoordinate(pos, GridCoordinate::SCREEN).toGrid();
        newPos.setX((int) (newPos.getX() + i));
        newPos.setY(newPos.getY());
        c->setPosition(newPos.toScreen());
        i++;
    }
}