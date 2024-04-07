/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../AGhost.hpp"

class Clyde: public AGhost {
public:
    Clyde();
    ~Clyde() override = default;

    void updateTarget(const APacManEntity &pac, const std::vector<AGhost *> &ghost) override;
    void recalculateDotLimit() override;
};
