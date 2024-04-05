/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../AGhost.hpp"

class Inky: public AGhost {
public:
    Inky();
    ~Inky() override = default;

    void updateTarget(const Pac &pac, const std::vector<AGhost *> &ghost) override;
    void recalculateDotLimit() override;
};
