/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Bonus.hpp"
#include "common/displayable/entities/SimpleSprite.hpp"
#include "../PacmanGlobals.hpp"

static std::string getPathFrom(BonusPoint points) {
    switch (points) {
        case _100:
        case _300:
        case _500:
        case _700:
        case _1000:
        case _2000:
        case _3000:
        case _5000:
            return "assets/games/pacman/bonus_fruits.png";
        case _200:
        case _400:
        case _1600:
        case _800:
            return "assets/games/pacman/bonus_ghost.png";
    }
}

static std::size_t getWidth(BonusPoint points) {
    switch (points) {
        case _100:
        case _300:
        case _500:
        case _700:
        case _1000:
        case _2000:
        case _3000:
        case _5000:
            return 160;
        case _200:
        case _400:
        case _1600:
        case _800:
            return 128;
    }
}

static std::size_t getHeight(BonusPoint points) {
    switch (points) {
        case _100:
        case _300:
        case _500:
        case _700:
        case _1000:
        case _2000:
        case _3000:
        case _5000:
            return 110;
        case _200:
        case _400:
        case _1600:
        case _800:
            return 14;
    }
}

Bonus::Bonus(const Coord2D& pos, BonusPoint points): AEntity(getPathFrom(points), getWidth(points), getHeight(points))
{
    this->_points = points;
    this->_apparitionTime = arcade->getTime();
    this->_canBeDeleted = false;
    this->setPosition(pos);
    this->setSize(SCALE * 8. / 20.);
    switch (points) {
        case _100:
            this->_sprite->setDrawRect({0, 0, 26, 14});
            break;
        case _200:
            this->_sprite->setDrawRect({0, 0, 30, 14});
            break;
        case _300:
            this->_sprite->setDrawRect({28, 0, 30, 14});
            break;
        case _400:
            this->_sprite->setDrawRect({30+2, 0, 30, 14});
            break;
        case _500:
            this->_sprite->setDrawRect({60, 0, 30, 14});
            break;
        case _700:
            this->_sprite->setDrawRect({92, 0, 30, 14});
            break;
        case _800:
            this->_sprite->setDrawRect({2*30+2*2, 0, 30, 14});
            break;
        case _1000:
            this->_sprite->setDrawRect({124, 0, 36, 14});
            break;
        case _1600:
            this->_sprite->setDrawRect({3*30+3*2, 0, 32, 14});
            break;
        case _2000:
            this->_sprite->setDrawRect({120, 18+14, 40, 14});
            break;
        case _3000:
            this->_sprite->setDrawRect({120, 2*18+2*14, 40, 14});
            break;
        case _5000:
            this->_sprite->setDrawRect({120, 3*18+3*14, 40, 14});
            break;
    }
}

Bonus::Bonus(const Bonus &bonus): AEntity(bonus.getSprite())
{
    this->_points = bonus._points;
    this->_apparitionTime = bonus._apparitionTime;
    this->_canBeDeleted = bonus._canBeDeleted;
}

Bonus &Bonus::operator=(const Bonus &bonus)
{
    this->_points = bonus._points;
    this->_apparitionTime = bonus._apparitionTime;
    this->_canBeDeleted = bonus._canBeDeleted;
    this->_sprite = std::make_unique<SimpleSprite>(bonus.getSprite());
    return *this;
}

bool Bonus::canBeDeleted() {
    if (arcade->getTime() - this->_apparitionTime > 1 * 1000) // Stays for 1 second
        this->_canBeDeleted = true;
    return this->_canBeDeleted;
}
