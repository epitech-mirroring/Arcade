/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../shared/IGame.hpp"

class AGame: public IGame {
protected:
    std::shared_ptr<IArcade> _arcade;
    int _score;

public:
    AGame();
    ~AGame() override;

    void init(std::shared_ptr<IArcade> arcade) override;
};