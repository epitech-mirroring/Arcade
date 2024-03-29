/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "common/AGame.hpp"

AGame::AGame() {
    this->_arcade = nullptr;
    this->_score = 0;
}

void AGame::init(IArcade &arcade) {
    this->_arcade = std::shared_ptr<IArcade>(&arcade);
}

int AGame::getScore() {
    return this->_score;
}
