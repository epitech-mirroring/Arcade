/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/displayable/entities/AEntity.hpp"
#include "common/utils/Coord2D.hpp"
#include "../PacManEnums.hpp"

class Bonus: public AEntity {
protected:
    BonusPoint _points;
    std::size_t _apparitionTime;
    bool _canBeDeleted;
public:
    Bonus(const Coord2D& pos, BonusPoint points);
    ~Bonus() override = default;
    Bonus(const Bonus &bonus);
    Bonus &operator=(const Bonus &bonus);

    [[nodiscard]] bool canBeDeleted();
};
