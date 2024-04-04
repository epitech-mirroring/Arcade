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
#include "Wall.hpp"
#include "APacManEntity.hpp"
#include "PacDot.hpp"
#include <vector>

#define SCALE_PACKMAN (SCALE * 8. / 26.)

class Pac : public APacManEntity {
protected:
    bool _eaten;
    std::size_t _animation;
public:
    Pac();
    ~Pac() override = default;
    Direction _newDirection;

    void handleEvent(const IEvent &event);
    void update(std::vector<PacDot *> &dots, const Wall (&map)[37][28]);
    [[nodiscard]] bool hasEaten() const;
    void setEaten(bool eaten);
};
