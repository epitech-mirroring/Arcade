/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Wall.hpp"
#include "../PacmanGlobals.hpp"

Wall::Wall(WallType type, bool isWhite): AEntity("assets/games/pacman/walls.png", 143, 26)
{
    this->_isWhite = isWhite;
    this->_type = type;
    this->setSize(SCALE);
    std::size_t tempType = type == WallType::DOT || type == WallType::ENERGIZER ? WallType::EMPTY : type;
    // Sprite is 143x26 with 16x3 sprites of 8x8 (there is a line of one pixel between each sprite)
    // type is 0-47 so we need to calculate the x and y
    std::size_t x = (tempType % 16) * 8;
    // Add offset caused by the line of one pixel between each sprite
    x += (tempType % 16);
    std::size_t y = (tempType / 16) * 8;
    // Add offset caused by the line of one pixel between each sprite
    y += (tempType / 16);
    this->_sprite->setDrawRect({x, y, 8, 8});
}

Wall::WallType Wall::getType() const {
    return this->_type;
}

bool Wall::isWhite() const {
    return this->_isWhite;
}
