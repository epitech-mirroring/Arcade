/*
** EPITECH PROJECT, 2024
** Pacman
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "common/displayable/entities/AEntity.hpp"
#include "shared/events/IEvent.hpp"
#include "shared/ICanDrawGizmos.hpp"
#include "shared/IArcade.hpp"
#include "../PacmanGlobals.hpp"

class APacManEntity: public AEntity {
protected:

    Direction _direction;
    APacManEntity(const std::string &texturePath, const std::size_t &sizeX, const std::size_t &sizeY);
public:
    ~APacManEntity() override = default;

    [[nodiscard]] Direction getDirection() const;
};
