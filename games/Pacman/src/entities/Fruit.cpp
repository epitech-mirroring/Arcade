/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Fruit.hpp"
#include "../PacmanGlobals.hpp"

static std::string getTexturePathFromType(BonusType type) {
    switch (type) {
        case BonusType::CHERRY:
            return "assets/games/pacman/bonus/Cherries.png";
        case BonusType::STRAWBERRY:
            return "assets/games/pacman/bonus/Strawberry.png";
        case BonusType::PEACH:
            return "assets/games/pacman/bonus/Peach.png";
        case BonusType::APPLE:
            return "assets/games/pacman/bonus/Apple.png";
        case BonusType::GRAPES:
            return "assets/games/pacman/bonus/Grapes.png";
        case BonusType::GALAXIAN:
            return "assets/games/pacman/bonus/Galaxian.png";
        case BonusType::BELL:
            return "assets/games/pacman/bonus/Bell.png";
        case BonusType::KEY:
            return "assets/games/pacman/bonus/Key.png";
    }
    return "";
}

static std::size_t getWidthFromType(BonusType type) {
    switch (type) {
        case BonusType::CHERRY:
        case BonusType::PEACH:
        case BonusType::APPLE:
        case BonusType::BELL:
            return 24;
        case BonusType::STRAWBERRY:
        case BonusType::GALAXIAN:
        case BonusType::GRAPES:
            return 22;
        case BonusType::KEY:
            return 14;
    }
    return 0;
}

static std::size_t getHeightFromType(BonusType type) {
    switch (type) {
        case BonusType::CHERRY:
        case BonusType::APPLE:
        case BonusType::STRAWBERRY:
        case BonusType::PEACH:
            return 24;
        case BonusType::KEY:
        case BonusType::BELL:
            return 26;
        case BonusType::GALAXIAN:
            return 22;
        case BonusType::GRAPES:
            return 28;
    }
    return 0;
}

Fruit::Fruit(BonusType type): AEntity(getTexturePathFromType(type),
                                      getWidthFromType(type),
                                        getHeightFromType(type)) {
    _type = type;
    this->setSize(SCALE * 8. / 24.);
    _hasBeenEaten = false;
    _apparitionTime = 0;
    _hasSpawned = false;
}

BonusType Fruit::getType() const {
    return _type;
}

bool Fruit::hasBeenEaten() const {
    return _hasBeenEaten;
}

void Fruit::setEaten(bool eaten) {
    _hasBeenEaten = eaten;
}

std::size_t Fruit::getApparitionTime() const {
    return _apparitionTime;
}

void Fruit::setApparitionTime(std::size_t apparitionTime) {
    _apparitionTime = apparitionTime;
}

bool Fruit::shouldBeDisplayed() const {
    return arcade->getTime() - _apparitionTime < 10000 && !_hasBeenEaten;
}

void Fruit::setSpawned(bool spawned) {
    _hasSpawned = spawned;
}

bool Fruit::hasSpawned() const {
    return _hasSpawned;
}
