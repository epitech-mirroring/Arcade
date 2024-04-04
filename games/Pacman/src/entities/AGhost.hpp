/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "shared/events/IEvent.hpp"
#include "shared/ICanDrawGizmos.hpp"
#include "shared/IArcade.hpp"
#include "../PacmanGlobals.hpp"
#include "APacManEntity.hpp"

class AGhost: public APacManEntity {
protected:
    bool _isDead;
    bool _hasToReverse;
    explicit AGhost(const std::string &texturePath);
public:
    ~AGhost() override = default;

    [[nodiscard]] bool isDead() const;
    [[nodiscard]] bool hasToReverse() const;
};
