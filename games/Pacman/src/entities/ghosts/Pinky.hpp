/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../AGhost.hpp"

class Pinky: public AGhost {
public:
    Pinky();
    ~Pinky() override = default;

    void updateTarget(const APacManEntity &pac, const std::vector<AGhost *> &ghost) override;
    void recalculateDotLimit() override;
};
