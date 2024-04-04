/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "../PacmanGlobals.hpp"
#include "common/displayable/entities/AEntity.hpp"

class PacDot : public AEntity {
protected:
    bool _isEnergizer;
public:
    explicit PacDot(bool isEnergizer = false);
    PacDot(PacDot &pacDot);
    ~PacDot() override = default;

    [[nodiscard]] bool isEnergizer() const;
    PacDot &operator=(const PacDot &pacDot);

};
