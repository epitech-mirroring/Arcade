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
    ~AGame() override = default;

    virtual void init(IArcade &arcade) override;
    virtual void start() override = 0;
    virtual void run() override = 0;
    virtual int getScore() override;
};
