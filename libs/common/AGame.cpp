/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "../../include/common/AGame.hpp"

AGame::AGame() {
    this->_arcade = nullptr;
    this->_score = 0;
}

AGame::~AGame() = default;

void AGame::init(std::shared_ptr<IArcade> arcade) {
    this->_arcade = arcade;
}
